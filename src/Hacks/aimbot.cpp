#include "aimbot.h"
#include "autowall.h"
#include "../interfaces.h"
#include <math.h>

// Default aimbot settings
bool Settings::Aimbot::enabled = true;
bool Settings::Aimbot::silent = false;
bool Settings::Aimbot::friendly = false;
int Settings::Aimbot::bone = BONE_HEAD;
ButtonCode_t Settings::Aimbot::aimkey = ButtonCode_t::MOUSE_MIDDLE;
bool Settings::Aimbot::aimkey_only = false;
bool Settings::Aimbot::Smooth::enabled = false;
float Settings::Aimbot::Smooth::value = 1.0f;
float Settings::Aimbot::Smooth::max = 1.0f;
bool Settings::Aimbot::ErrorMargin::enabled = false;
float Settings::Aimbot::ErrorMargin::value = 0.0f;
bool Settings::Aimbot::AutoAim::enabled = false;
float Settings::Aimbot::AutoAim::fov = 180.0f;
bool Settings::Aimbot::AutoWall::enabled = false;
float Settings::Aimbot::AutoWall::value = 10.0f;
bool Settings::Aimbot::AutoWall::bones[] = { true, false, false, false, false, false };
bool Settings::Aimbot::AimStep::enabled = false;
float Settings::Aimbot::AimStep::value = 25.0f;
bool Settings::Aimbot::AutoPistol::enabled = false;
bool Settings::Aimbot::AutoShoot::enabled = false;
bool Settings::Aimbot::AutoShoot::autoscope = false;
bool Settings::Aimbot::RCS::enabled = false;
bool Settings::Aimbot::RCS::always_on = false;
float Settings::Aimbot::RCS::value = 2.0f;
bool Settings::Aimbot::AutoCrouch::enabled = false;
bool Settings::Aimbot::AutoStop::enabled = false;
bool Settings::Aimbot::NoShoot::enabled = false;
bool Settings::Aimbot::IgnoreJump::enabled = false;
bool Settings::Aimbot::SmokeCheck::enabled = false;
bool Settings::Aimbot::Smooth::Salting::enabled = false;
float Settings::Aimbot::Smooth::Salting::multiplier = 0.0f;

bool Aimbot::AimStepInProgress = false;
std::vector<int64_t> Aimbot::Friends = { };

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

void GetBestBone(C_BasePlayer* player, float& best_damage, Bone& best_bone)
{
	best_bone = BONE_HEAD;

	for (std::unordered_map<int, std::vector<const char*>>::iterator it = hitboxes.begin(); it != hitboxes.end(); it++)
	{
		if (!Settings::Aimbot::AutoWall::bones[it->first])
			continue;

		std::vector<const char*> hitboxList = hitboxes[it->first];
		for (std::vector<const char*>::iterator it2 = hitboxList.begin(); it2 != hitboxList.end(); it2++)
		{
			Bone bone = (Bone) Entity::GetBoneByName(player, *it2);
			Vector vec_bone = player->GetBonePosition(bone);

			Autowall::FireBulletData data;
			float damage = Autowall::GetDamage(vec_bone, !Settings::Aimbot::friendly, data);

			if (damage > best_damage)
			{
				best_damage = damage;
				best_bone = bone;
			}
		}
	}
}

C_BasePlayer* GetClosestPlayer(CUserCmd* cmd, bool visible, Bone& best_bone, AimTargetType aimTargetType = AimTargetType::FOV)
{
	best_bone = static_cast<Bone>(Settings::Aimbot::bone);

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	C_BasePlayer* closestEntity = NULL;

	// TODO Change the big value with a distance/fov slider
	float best_fov = Settings::Aimbot::AutoAim::fov;
	float best_distance = 999999999.0f;
	int best_hp = 100;
	float best_damage = 0;

	if (!localplayer)
		return NULL;

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BasePlayer* player = (C_BasePlayer*) entitylist->GetClientEntity(i);

		if (!player
			|| player == localplayer
			|| player->GetDormant()
			|| !player->GetAlive()
			|| player->GetImmune())
			continue;

		if (!Settings::Aimbot::friendly && player->GetTeam() == localplayer->GetTeam())
			continue;

		IEngineClient::player_info_t entityInformation;
		engine->GetPlayerInfo(i, &entityInformation);

		if (std::find(Aimbot::Friends.begin(), Aimbot::Friends.end(), entityInformation.xuid) != Aimbot::Friends.end())
			continue;

		Vector e_vecHead = player->GetBonePosition(Settings::Aimbot::bone);
		Vector p_vecHead = localplayer->GetEyePosition();

		QAngle viewAngles;
		engine->GetViewAngles(viewAngles);

		float fov = Math::GetFov(viewAngles, Math::CalcAngle(p_vecHead, e_vecHead));
		float distance = Math::GetDistance(p_vecHead, e_vecHead);
		int hp = player->GetHealth();

		if (aimTargetType == AimTargetType::DISTANCE && distance > best_distance)
			continue;

		if (aimTargetType == AimTargetType::FOV && fov > best_fov)
			continue;

		if (aimTargetType == AimTargetType::HP && hp > best_hp)
			continue;

		if (visible && !Entity::IsVisible(player, Settings::Aimbot::bone) && !Settings::Aimbot::AutoWall::enabled)
			continue;

		if (Settings::Aimbot::AutoWall::enabled)
		{
			float damage = 0.0f;
			Bone bone;
			GetBestBone(player, damage, bone);

			if (damage >= best_damage && damage >= Settings::Aimbot::AutoWall::value)
			{
				best_damage = damage;
				best_bone = bone;
				closestEntity = player;
			}
		}
		else
		{
			closestEntity = player;
			best_fov = fov;
			best_distance = distance;
			best_hp = hp;
		}
	}

	return closestEntity;
}

void Aimbot::RCS(QAngle& angle, C_BasePlayer* player, CUserCmd* cmd)
{
	if (!Settings::Aimbot::RCS::enabled)
		return;

	if (!(cmd->buttons & IN_ATTACK))
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	QAngle CurrentPunch = localplayer->GetAimPunchAngle();
	bool isSilent = Settings::Aimbot::silent;
	bool hasTarget = Settings::Aimbot::AutoAim::enabled && player && shouldAim;

	if (!Settings::Aimbot::RCS::always_on && !hasTarget)
		return;

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

void Aimbot::AimStep(C_BasePlayer* player, QAngle& angle, CUserCmd* cmd)
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

	if (!player)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	Vector e_vecHead = player->GetBonePosition(Settings::Aimbot::bone);
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

void Salt(float& smooth)
{
	float sine = sin (globalvars->tickcount);
	float salt = sine * Settings::Aimbot::Smooth::Salting::multiplier;
	float oval = smooth + salt;
	smooth *= oval;
}

void Aimbot::Smooth(C_BasePlayer* player, QAngle& angle, CUserCmd* cmd)
{
	if (!Settings::Aimbot::Smooth::enabled)
		return;

	if (Settings::AntiAim::Pitch::enabled || Settings::AntiAim::Yaw::enabled)
		return;

	if (!shouldAim || !player)
		return;

	if (Settings::Aimbot::silent)
		return;

	QAngle viewAngles;
	engine->GetViewAngles(viewAngles);

	QAngle delta = angle - viewAngles;
	Math::NormalizeAngles(delta);

	float smooth = powf(Settings::Aimbot::Smooth::value, 0.4f); // Makes more slider space for actual useful values

	if (Settings::Aimbot::Smooth::Salting::enabled)
	{
		Salt(smooth);
	}

	// For convenience
	// Because of the powf, when the slider is 0.02, the smooth value is 0.02^0.4 = ~0.21
	if (Settings::Aimbot::Smooth::value < 0.02f)
		smooth = 0.0f;

	// When smooth is 1 it doesn't move at all, useless to have that on the slider
	if (Settings::Aimbot::Smooth::value > 0.99f)
		smooth = 0.99f;

	QAngle toChange = delta - delta * smooth;
	angle = viewAngles + toChange;
}

void Aimbot::ConstSpeedSmooth(C_BasePlayer* player, QAngle& angle, CUserCmd* cmd)
{
	if (!Settings::Aimbot::Smooth::enabled)
		return;

	if (Settings::AntiAim::Pitch::enabled || Settings::AntiAim::Yaw::enabled)
		return;

	if (!shouldAim || !player)
		return;

	if (Settings::Aimbot::silent)
		return;

	QAngle viewAngles;
	engine->GetViewAngles(viewAngles);

	QAngle delta = angle - viewAngles;
	Math::NormalizeAngles(delta);

	float smooth = Settings::Aimbot::Smooth::value / Settings::Aimbot::Smooth::max;

	if (Settings::Aimbot::Smooth::Salting::enabled)
	{
		Salt(smooth);
	}

	float slope = delta.y / delta.x;

	/*
	 * Will only happen if delta.x is really small, the limit as x-> 0 is infinity,
	 * so estimate with a big ass number.
	 */
	if (slope != slope) // is NaN
		slope = 9999999;

	slope = fabs(slope);
	float theta = atan(slope);

	float changeFactor = Settings::Aimbot::Smooth::max - (smooth * Settings::Aimbot::Smooth::max);

	float factorx = changeFactor * cos(theta);
	float factory = changeFactor * sin(theta);

	if (delta.x < 0.0f)
	{
		if (factorx > fabs(delta.x))
			factorx = fabs(delta.x);

		angle.x = viewAngles.x - factorx;
	}
	else
	{
		if (factorx > delta.x)
			factorx = delta.x;

		angle.x = viewAngles.x + factorx;
	}

	if (delta.y < 0.0f)
	{
		if (factory > fabs(delta.y))
			factory = fabs(delta.y);

		angle.y = viewAngles.y - factory;
	}
	else
	{
		if (factory > delta.y)
			factory = delta.y;

		angle.y = viewAngles.y + factory;
	}
}

void Aimbot::AutoCrouch(C_BasePlayer* player, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoCrouch::enabled)
		return;

	if (!player)
		return;

	cmd->buttons |= IN_DUCK;
}

void Aimbot::AutoStop(C_BasePlayer* player, float& forward, float& sideMove, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoStop::enabled)
		return;

	if (!player)
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

void Aimbot::AutoShoot(C_BasePlayer* player, C_BaseCombatWeapon* active_weapon, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoShoot::enabled)
		return;

	if (Settings::Aimbot::AimStep::enabled && Aimbot::AimStepInProgress)
		return;

	if (!player || !active_weapon || active_weapon->IsKnife() || active_weapon->GetAmmo() == 0)
		return;

	if (cmd->buttons & IN_USE)
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

	if (!Settings::AntiAim::Pitch::enabled && !Settings::AntiAim::Yaw::enabled)
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

void Aimbot::NoShoot(C_BaseCombatWeapon* active_weapon, C_BasePlayer* player, CUserCmd* cmd)
{
	if (player && Settings::Aimbot::NoShoot::enabled)
	{
		if (*active_weapon->GetItemDefinitionIndex() == WEAPON_C4)
			return;

		if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			cmd->buttons &= ~IN_ATTACK2;
		else
			cmd->buttons &= ~IN_ATTACK;
	}
}

void Aimbot::CreateMove(CUserCmd* cmd)
{
	if (!Settings::Aimbot::enabled)
		return;

	QAngle oldAngle;
	engine->GetViewAngles(oldAngle);
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	shouldAim = Settings::Aimbot::AutoShoot::enabled;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if (Settings::Aimbot::IgnoreJump::enabled && !(localplayer->GetFlags() & FL_ONGROUND))
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon || active_weapon->GetInReload() || active_weapon->IsGrenade() || active_weapon->IsKnife() || active_weapon->IsBomb())
		return;

	Bone aw_bone;
	C_BasePlayer* player = GetClosestPlayer(cmd, true, aw_bone);

	if (player)
	{
		Vector e_vecHead = player->GetBonePosition(aw_bone);
		Vector p_vecHead = localplayer->GetEyePosition();

		if (Settings::Aimbot::SmokeCheck::enabled && LineGoesThroughSmoke(p_vecHead, e_vecHead, true))
			return;

		if (Settings::Aimbot::AutoAim::enabled)
		{
			if (cmd->buttons & IN_ATTACK && !Settings::Aimbot::aimkey_only)
				shouldAim = true;

			if (input->IsButtonDown(Settings::Aimbot::aimkey))
				shouldAim = true;

			if (shouldAim)
			{
				angle = Math::CalcAngle(p_vecHead, e_vecHead);

				if (Settings::Aimbot::ErrorMargin::enabled)
					ApplyErrorToAngle(&angle, Settings::Aimbot::ErrorMargin::value);
			}
		}
	}
	Aimbot::AimStep(player, angle, cmd);
	Aimbot::AutoCrouch(player, cmd);
	Aimbot::AutoStop(player, oldForward, oldSideMove, cmd);
	Aimbot::AutoPistol(active_weapon, cmd);
	Aimbot::AutoShoot(player, active_weapon, cmd);
	Aimbot::RCS(angle, player, cmd);
	Aimbot::Smooth(player, angle, cmd);
	Aimbot::ShootCheck(active_weapon, cmd);
	Aimbot::NoShoot(active_weapon, player, cmd);

	Math::NormalizeAngles(angle);
	Math::ClampAngles(angle);
	cmd->viewangles = angle;
	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);

	if (!Settings::Aimbot::silent)
		engine->SetViewAngles(cmd->viewangles);
}

void Aimbot::FireEventClientSide(IGameEvent* event)
{
	if (!event)
		return;

	if (strcmp(event->GetName(), "player_connect_full") == 0 || strcmp(event->GetName(), "cs_game_disconnected") == 0)
	{
		if (event->GetInt("userid") && engine->GetPlayerForUserID(event->GetInt("userid")) != engine->GetLocalPlayer())
			return;

		Aimbot::Friends.clear();
	}
}
