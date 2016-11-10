#include "aimbot.h"
#include "autowall.h"

// Default aimbot settings
bool Settings::Aimbot::enabled = true;
bool Settings::Aimbot::silent = false;
bool Settings::Aimbot::friendly = false;
float Settings::Aimbot::fov = 180.0f;
float Settings::Aimbot::errorMargin = 0.0F;
unsigned int Settings::Aimbot::bone = BONE_HEAD;
ButtonCode_t Settings::Aimbot::aimkey = ButtonCode_t::MOUSE_MIDDLE;
bool Settings::Aimbot::aimkey_only = false;
bool Settings::Aimbot::Smooth::enabled = false;
float Settings::Aimbot::Smooth::value = 1.0f;
float Settings::Aimbot::Smooth::max = 15.0f;
bool Settings::Aimbot::AutoAim::enabled = false;
bool Settings::Aimbot::AutoWall::enabled = false;
float Settings::Aimbot::AutoWall::value = 10.0f;
std::vector<Hitbox> Settings::Aimbot::AutoWall::bones = { HITBOX_HEAD };
bool Settings::Aimbot::AimStep::enabled = false;
float Settings::Aimbot::AimStep::value = 25.0f;
bool Settings::Aimbot::AutoPistol::enabled = false;
bool Settings::Aimbot::AutoShoot::enabled = false;
bool Settings::Aimbot::AutoShoot::autoscope = false;
bool Settings::Aimbot::RCS::enabled = false;
float Settings::Aimbot::RCS::value = 2.0f;
bool Settings::Aimbot::AutoCrouch::enabled = false;
bool Settings::Aimbot::AutoStop::enabled = false;
bool Settings::Aimbot::Smooth::Salting::enabled = false;
float Settings::Aimbot::Smooth::Salting::percentage = 0.0f;
bool Aimbot::AimStepInProgress = false;

bool shouldAim;
QAngle AimStepLastAngle;
QAngle RCSLastPunch;

std::unordered_map<int, std::vector<const char*>> hitboxes = {
		{ HITBOX_HEAD, { "head_0" } },
		{ HITBOX_NECK, { "neck_0" } },
		{ HITBOX_PELVIS, { "pelvis" } },
		{ HITBOX_SPINE, { "spine_0", "spine_1", "spine_2", "spine_3" } },
		{ HITBOX_LEGS, { "leg_upper_L", "leg_upper_R", "leg_lower_L", "leg_lower_R", "ankle_L", "ankle_R" } },
		{ HITBOX_ARMS, { "hand_L", "hand_R", "arm_upper_L", "arm_lower_L", "arm_upper_R", "arm_lower_R" } },
};

static void ApplyErrorToAngle(QAngle* angles, float margin)
{
	QAngle error;
	error.Random(-1.0f, 1.0f);
	error *= margin;
	angles->operator+=(error);
}

void GetBestBone(C_BaseEntity* entity, float& best_damage, Bone& best_bone)
{
	best_bone = BONE_HEAD;

	for (std::vector<Hitbox>::iterator it = Settings::Aimbot::AutoWall::bones.begin(); it != Settings::Aimbot::AutoWall::bones.end(); it++)
	{
		std::vector<const char*> hitboxList = hitboxes[*it];

		for (std::vector<const char*>::iterator it2 = hitboxList.begin(); it2 != hitboxList.end(); it2++)
		{
			Bone bone = (Bone) Entity::GetBoneByName(entity, *it2);
			Vector vec_bone = entity->GetBonePosition(bone);

			float damage = Autowall::GetDamage(vec_bone);

			if (damage > best_damage)
			{
				best_damage = damage;
				best_bone = bone;
			}
		}
	}
}

C_BaseEntity* GetClosestEnemy(CUserCmd* cmd, bool visible, Bone& best_bone)
{
	best_bone = static_cast<Bone>(Settings::Aimbot::bone);
	
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	C_BaseEntity* closestEntity = NULL;
	float best_fov = Settings::Aimbot::fov;
	float best_damage = 0;

	if (!localplayer)
		return NULL;

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BaseEntity* entity = entitylist->GetClientEntity(i);

		if (!entity
			|| entity == localplayer
			|| entity->GetDormant()
			|| !entity->GetAlive()
			|| entity->GetImmune())
			continue;

		if (!Settings::Aimbot::friendly && entity->GetTeam() == localplayer->GetTeam())
			continue;

		Vector e_vecHead = entity->GetBonePosition(Settings::Aimbot::bone);
		Vector p_vecHead = localplayer->GetEyePosition();
		float fov = Math::GetFov(cmd->viewangles, Math::CalcAngle(p_vecHead, e_vecHead));

		if (fov > best_fov)
			continue;

		if (visible && !Entity::IsVisible(entity, Settings::Aimbot::bone) && !Settings::Aimbot::AutoWall::enabled)
			continue;

		if (Settings::Aimbot::AutoWall::enabled)
		{
			float damage = 0.0f;
			Bone bone;
			GetBestBone(entity, damage, bone);
			
			if (damage >= best_damage && damage >= Settings::Aimbot::AutoWall::value)
			{
				best_damage = damage;
				best_bone = bone;
				closestEntity = entity;
			}
		}
		else
		{
			closestEntity = entity;
			best_fov = fov;
		}
	}

	return closestEntity;
}

void Aimbot::RCS(QAngle& angle, C_BaseEntity* entity, CUserCmd* cmd)
{
	if (!Settings::Aimbot::RCS::enabled)
		return;

	if (!(cmd->buttons & IN_ATTACK))
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	QAngle CurrentPunch = localplayer->GetAimPunchAngle();
	bool isSilent = Settings::Aimbot::silent;
	bool hasTarget = Settings::Aimbot::AutoAim::enabled && entity != NULL && shouldAim;

	if (isSilent || hasTarget)
	{
		angle -= CurrentPunch * Settings::Aimbot::RCS::value;
	}
	else if (localplayer->GetShotsFired() > 1)
	{
		QAngle NewPunch = { CurrentPunch.x - RCSLastPunch.x, CurrentPunch.y - RCSLastPunch.y, 0 };

		angle -= NewPunch * Settings::Aimbot::RCS::value;
	}

	RCSLastPunch = CurrentPunch;
}

void Aimbot::AimStep(C_BaseEntity* entity, QAngle& angle, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AimStep::enabled)
		return;

	if (!Settings::Aimbot::AutoAim::enabled)
		return;

	if (Settings::Aimbot::Smooth::enabled)
		return;

	if (!shouldAim)
		return;

	if (!Aimbot::AimStepInProgress)
		AimStepLastAngle = cmd->viewangles;

	if (!entity)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	Vector e_vecHead = entity->GetBonePosition(Settings::Aimbot::bone);
	Vector p_vecHead = localplayer->GetEyePosition();
	float fov = Math::GetFov(AimStepLastAngle, Math::CalcAngle(p_vecHead, e_vecHead));

	Aimbot::AimStepInProgress = fov > Settings::Aimbot::AimStep::value;

	if (!Aimbot::AimStepInProgress)
		return;

	QAngle AimStepDelta = AimStepLastAngle - angle;

	if (AimStepDelta.y < 0)
		AimStepLastAngle.y += Settings::Aimbot::AimStep::value;
	else
		AimStepLastAngle.y -= Settings::Aimbot::AimStep::value;

	AimStepLastAngle.x = angle.x;
	angle = AimStepLastAngle;
}

float RandomNumber(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

void Aimbot::Smooth(C_BaseEntity* entity, QAngle& angle, CUserCmd* cmd)
{
	if (!Settings::Aimbot::Smooth::enabled)
		return;

	if (Settings::AntiAim::enabled_X || Settings::AntiAim::enabled_Y)
		return;

	if (!entity)
		return;

	QAngle delta = angle - cmd->viewangles;
	Math::NormalizeAngles(delta);
	
	float smooth = Settings::Aimbot::Smooth::value / Settings::Aimbot::Smooth::max;
	
	if (Settings::Aimbot::Smooth::Salting::enabled)
	{
		float max_remove = Settings::Aimbot::Smooth::value - (((100 - Settings::Aimbot::Smooth::Salting::percentage) / 100) * Settings::Aimbot::Smooth::value);
		float remove = RandomNumber (0.0f, max_remove);
		
		smooth -= remove;
	}
	
	float factorx = 1.0f - smooth;
	float factory = 1.0f - smooth;

	if (delta.x < 0.0f)
	{
		if (factorx > fabs(delta.x))
			factorx = fabs(delta.x);

		angle.x = cmd->viewangles.x - factorx;
	}
	else
	{
		if (factorx > delta.x)
			factorx = delta.x;

		angle.x = cmd->viewangles.x + factorx;
	}

	if (delta.y < 0.0f)
	{
		if (factory > fabs(delta.y))
			factory = fabs(delta.y);

		angle.y = cmd->viewangles.y - factory;
	}
	else
	{
		if (factory > delta.y)
			factory = delta.y;

		angle.y = cmd->viewangles.y + factory;
	}
}

void Aimbot::AutoCrouch(C_BaseEntity* entity, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoCrouch::enabled)
		return;

	if (!entity)
		return;

	cmd->buttons |= IN_DUCK;
}

void Aimbot::AutoStop(C_BaseEntity* entity, float& forward, float& sideMove, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoStop::enabled)
		return;

	if (!entity)
		return;

	forward = 0;
	sideMove = 0;
	cmd->upmove = 0;
}

void Aimbot::AutoPistol(C_BaseCombatWeapon* active_weapon, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoPistol::enabled)
		return;

	if (!active_weapon || !active_weapon->IsPistol())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	float nextPrimaryAttack = active_weapon->GetNextPrimaryAttack();
	float tick = localplayer->GetTickBase() * globalvars->interval_per_tick;

	if (nextPrimaryAttack < tick)
		return;

	if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
		cmd->buttons &= ~IN_ATTACK2;
	else
		cmd->buttons &= ~IN_ATTACK;
}

void Aimbot::AutoShoot(C_BaseEntity* entity, C_BaseCombatWeapon* active_weapon, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoShoot::enabled)
		return;

	if (Settings::Aimbot::AimStep::enabled && Aimbot::AimStepInProgress)
		return;

	if (!entity || !active_weapon || active_weapon->IsKnife() || active_weapon->GetAmmo() == 0)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	float nextPrimaryAttack = active_weapon->GetNextPrimaryAttack();
	float tick = localplayer->GetTickBase() * globalvars->interval_per_tick;

	if (nextPrimaryAttack > tick)
	{
		if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			cmd->buttons &= ~IN_ATTACK2;
		else
			cmd->buttons &= ~IN_ATTACK;
	}
	else
	{
		if (Settings::Aimbot::AutoShoot::autoscope && active_weapon->CanScope() && !localplayer->IsScoped())
			cmd->buttons |= IN_ATTACK2;
		else if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			cmd->buttons |= IN_ATTACK2;
		else
			cmd->buttons |= IN_ATTACK;
	}
}

void Aimbot::ShootCheck(C_BaseCombatWeapon* active_weapon, CUserCmd* cmd)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	float nextPrimaryAttack = active_weapon->GetNextPrimaryAttack();
	float tick = localplayer->GetTickBase() * globalvars->interval_per_tick;

	if (!Settings::AntiAim::enabled_X && !Settings::AntiAim::enabled_Y)
		return;

	if (!Settings::Aimbot::silent)
		return;

	if (!(cmd->buttons & IN_ATTACK))
		return;
	
	if (nextPrimaryAttack < tick)
		return;

	if (*active_weapon->GetItemDefinitionIndex() == WEAPON_C4)
		return;

	if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
		cmd->buttons &= ~IN_ATTACK2;
	else
		cmd->buttons &= ~IN_ATTACK;
}

void Aimbot::CreateMove(CUserCmd* cmd)
{
	if (!Settings::Aimbot::enabled)
		return;

	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	shouldAim = Settings::Aimbot::AutoShoot::enabled;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon || active_weapon->GetInReload() || active_weapon->IsGrenade() || active_weapon->IsKnife())
		return;

	Bone aw_bone;
	C_BaseEntity* entity = GetClosestEnemy(cmd, true, aw_bone);
	if (entity && Settings::Aimbot::AutoAim::enabled)
	{
		if (cmd->buttons & IN_ATTACK && !Settings::Aimbot::aimkey_only)
			shouldAim = true;

		if (!(cmd->buttons & IN_ATTACK) && input->IsButtonDown(Settings::Aimbot::aimkey))
			shouldAim = true;

		if (shouldAim)
		{
			Vector e_vecHead = entity->GetBonePosition(aw_bone);
			Vector p_vecHead = localplayer->GetEyePosition();

			angle = Math::CalcAngle(p_vecHead, e_vecHead);
			ApplyErrorToAngle(&angle, Settings::Aimbot::errorMargin);
		}
	}

	Aimbot::AimStep(entity, angle, cmd);
	Aimbot::AutoCrouch(entity, cmd);
	Aimbot::AutoStop(entity, oldForward, oldSideMove, cmd);
	Aimbot::AutoPistol(active_weapon, cmd);
	Aimbot::AutoShoot(entity, active_weapon, cmd);
	Aimbot::RCS(angle, entity, cmd);
	Aimbot::Smooth(entity, angle, cmd);
	Aimbot::ShootCheck(active_weapon, cmd);

	Math::NormalizeAngles(angle);
	Math::ClampAngles(angle);
	cmd->viewangles = angle;
	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);

	if (!Settings::Aimbot::silent)
		engine->SetViewAngles(cmd->viewangles);
}
