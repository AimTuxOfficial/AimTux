#include "aimbot.h"
#include "autowall.h"
#include "../interfaces.h"
#include <math.h>

// Default aimbot settings
bool Settings::Aimbot::enabled = false;
bool Settings::Aimbot::silent = false;
bool Settings::Aimbot::friendly = false;
int Settings::Aimbot::bone = BONE_HEAD;
ButtonCode_t Settings::Aimbot::aimkey = ButtonCode_t::MOUSE_MIDDLE;
bool Settings::Aimbot::aimkey_only = false;
bool Settings::Aimbot::Smooth::enabled = false;
float Settings::Aimbot::Smooth::value = 0.5f;
int Settings::Aimbot::Smooth::type = SmoothType::SLOW_END;
bool Settings::Aimbot::ErrorMargin::enabled = false;
float Settings::Aimbot::ErrorMargin::value = 0.0f;
bool Settings::Aimbot::AutoAim::enabled = false;
float Settings::Aimbot::AutoAim::fov = 180.0f;
bool Settings::Aimbot::AutoAim::real_distance = false;
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

std::unordered_map<int, Settings::Aimbot::Weapon> Settings::Aimbot::weapons = {
		{ -1, Settings::Aimbot::Weapon(false, false, false, BONE_HEAD, ButtonCode_t::MOUSE_MIDDLE, false, false, 1.0f, SmoothType::SLOW_END, false, 0.0f, false, 0.0f, true, 180.0f, false, 25.0f, false, false, 2.0f, false, false, false, false, false, false, false, 10.0f, &Settings::Aimbot::AutoWall::bones[0], false) },
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

float GetRealDistanceFOV(float distance, QAngle angle, CUserCmd* cmd)
{
	/*    n
	    w + e
	      s        'real distance'
	                      |
	   a point -> x --..  v
	              |     ''-- x <- a guy
	              |          /
	             |         /
	             |       /
	            | <------------ both of these lines are the same length
	            |    /      /
	           |   / <-----'
	           | /
	          o
	     localplayer
	*/

	Vector aimingAt;
	Math::AngleVectors(cmd->viewangles, aimingAt);
	aimingAt *= distance;

	Vector aimAt;
	Math::AngleVectors(angle, aimAt);
	aimAt *= distance;

	return Math::GetDistance(aimingAt, aimAt);
}

C_BasePlayer* GetClosestPlayer(CUserCmd* cmd, bool visible, Bone& best_bone, AimTargetType aimTargetType = AimTargetType::FOV)
{
	if (Settings::Aimbot::AutoAim::real_distance)
		aimTargetType = AimTargetType::REAL_DISTANCE;

	best_bone = static_cast<Bone>(Settings::Aimbot::bone);

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	C_BasePlayer* closestEntity = NULL;

	// TODO Change the big value with a distance/fov slider
	float best_fov = Settings::Aimbot::AutoAim::fov;
	float best_real_distance = Settings::Aimbot::AutoAim::fov * 5.f;
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

		float distance = Math::GetDistance(p_vecHead, e_vecHead);
		float fov = Math::GetFov(viewAngles, Math::CalcAngle(p_vecHead, e_vecHead));
		float real_distance = GetRealDistanceFOV(distance, Math::CalcAngle(p_vecHead, e_vecHead), cmd);
		int hp = player->GetHealth();

		if (aimTargetType == AimTargetType::DISTANCE && distance > best_distance)
			continue;

		if (aimTargetType == AimTargetType::FOV && fov > best_fov)
			continue;

		if (aimTargetType == AimTargetType::REAL_DISTANCE && real_distance > best_real_distance)
			continue;

		if (aimTargetType == AimTargetType::HP && hp > best_hp)
			continue;

		if (visible && !Settings::Aimbot::AutoWall::enabled && !Entity::IsVisible(player, Settings::Aimbot::bone))
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
			best_real_distance = real_distance;
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

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	QAngle CurrentPunch = *localplayer->GetAimPunchAngle();
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

	QAngle viewAngles = QAngle(0.f, 0.f, 0.f);
	engine->GetViewAngles(viewAngles);

	QAngle delta = angle - viewAngles;
	Math::NormalizeAngles(delta);

	float smooth = powf(Settings::Aimbot::Smooth::value, 0.4f); // Makes more slider space for actual useful values

	smooth = std::min(0.99f, smooth);

	if (Settings::Aimbot::Smooth::Salting::enabled)
	{
		Salt(smooth);
	}

	QAngle toChange = QAngle(0.f, 0.f, 0.f);

	if (Settings::Aimbot::Smooth::type == SmoothType::SLOW_END)
	{
		toChange = delta - delta * smooth;
	}
	else if (Settings::Aimbot::Smooth::type == SmoothType::CONSTANT)
	{
		float coeff = fabsf(smooth - 1.f) / delta.Length() * 4.f;
		coeff = std::min(1.f, coeff);
		toChange = (delta * coeff);
	}

	angle = viewAngles + toChange;
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

	if (!active_weapon || active_weapon->GetCSWpnData()->GetWeaponType() != WEAPONTYPE_PISTOL)
		return;

	if (active_weapon->GetNextPrimaryAttack() < globalvars->curtime)
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

	if (!player || !active_weapon || active_weapon->GetAmmo() == 0)
		return;

	CSWeaponType weaponType = active_weapon->GetCSWpnData()->GetWeaponType();
	if (weaponType == WEAPONTYPE_KNIFE || weaponType == WEAPONTYPE_C4 || weaponType == WEAPONTYPE_GRENADE)
		return;

	if (cmd->buttons & IN_USE)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	float nextPrimaryAttack = active_weapon->GetNextPrimaryAttack();

	if (nextPrimaryAttack > globalvars->curtime)
	{
		if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			cmd->buttons &= ~IN_ATTACK2;
		else
			cmd->buttons &= ~IN_ATTACK;
	}
	else
	{
		if (Settings::Aimbot::AutoShoot::autoscope && active_weapon->GetCSWpnData()->GetZoomLevels() > 0 && !localplayer->IsScoped())
			cmd->buttons |= IN_ATTACK2;
		else if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			cmd->buttons |= IN_ATTACK2;
		else
			cmd->buttons |= IN_ATTACK;
	}
}

void Aimbot::ShootCheck(C_BaseCombatWeapon* active_weapon, CUserCmd* cmd)
{
	if (!Settings::AntiAim::Pitch::enabled && !Settings::AntiAim::Yaw::enabled)
		return;

	if (!Settings::Aimbot::silent)
		return;

	if (!(cmd->buttons & IN_ATTACK))
		return;

	if (active_weapon->GetNextPrimaryAttack() < globalvars->curtime)
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
	Aimbot::UpdateValues();

	if (!Settings::Aimbot::enabled)
		return;

	QAngle oldAngle;
	engine->GetViewAngles(oldAngle);
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	shouldAim = Settings::Aimbot::AutoShoot::enabled;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if (Settings::Aimbot::IgnoreJump::enabled && !(localplayer->GetFlags() & FL_ONGROUND))
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*) entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon || active_weapon->GetInReload())
		return;

	CSWeaponType weaponType = active_weapon->GetCSWpnData()->GetWeaponType();
	if (weaponType == WEAPONTYPE_C4 || weaponType == WEAPONTYPE_GRENADE || weaponType == WEAPONTYPE_KNIFE)
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

	if (angle != cmd->viewangles)
	{
		Math::NormalizeAngles(angle);
		Math::ClampAngles(angle);
		cmd->viewangles = angle;
		Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);

		if (!Settings::Aimbot::silent)
			engine->SetViewAngles(cmd->viewangles);
	}
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

void Aimbot::UpdateValues()
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*) entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon)
		return;

	int index = -1;
	if (Settings::Aimbot::weapons.find(*active_weapon->GetItemDefinitionIndex()) != Settings::Aimbot::weapons.end())
		index = *active_weapon->GetItemDefinitionIndex();

	Settings::Aimbot::Weapon currentWeaponSetting = Settings::Aimbot::weapons[index];

	Settings::Aimbot::enabled = currentWeaponSetting.enabled;
	Settings::Aimbot::silent = currentWeaponSetting.silent;
	Settings::Aimbot::friendly = currentWeaponSetting.friendly;
	Settings::Aimbot::bone = currentWeaponSetting.bone;
	Settings::Aimbot::aimkey = currentWeaponSetting.aimkey;
	Settings::Aimbot::aimkey_only = currentWeaponSetting.aimkey_only;
	Settings::Aimbot::Smooth::enabled = currentWeaponSetting.smoothEnabled;
	Settings::Aimbot::Smooth::value = currentWeaponSetting.smoothAmount;
	Settings::Aimbot::Smooth::type = currentWeaponSetting.smoothType;
	Settings::Aimbot::ErrorMargin::enabled = currentWeaponSetting.errorMarginEnabled;
	Settings::Aimbot::ErrorMargin::value = currentWeaponSetting.errorMarginValue;
	Settings::Aimbot::AutoAim::enabled = currentWeaponSetting.autoAimEnabled;
	Settings::Aimbot::AutoAim::fov = currentWeaponSetting.autoAimFov;
	Settings::Aimbot::AimStep::enabled = currentWeaponSetting.aimStepEnabled;
	Settings::Aimbot::AimStep::value = currentWeaponSetting.aimStepValue;
	Settings::Aimbot::AutoPistol::enabled = currentWeaponSetting.autoPistolEnabled;
	Settings::Aimbot::AutoShoot::enabled = currentWeaponSetting.autoShootEnabled;
	Settings::Aimbot::AutoShoot::autoscope = currentWeaponSetting.autoScopeEnabled;
	Settings::Aimbot::RCS::enabled = currentWeaponSetting.rcsEnabled;
	Settings::Aimbot::RCS::always_on = currentWeaponSetting.rcsAlways_on;
	Settings::Aimbot::RCS::value = currentWeaponSetting.rcsAmount;
	Settings::Aimbot::NoShoot::enabled = currentWeaponSetting.noShootEnabled;
	Settings::Aimbot::IgnoreJump::enabled = currentWeaponSetting.ignoreJumpEnabled;
	Settings::Aimbot::Smooth::Salting::enabled = currentWeaponSetting.smoothSaltEnabled;
	Settings::Aimbot::Smooth::Salting::multiplier = currentWeaponSetting.smoothSaltMultiplier;
	Settings::Aimbot::SmokeCheck::enabled = currentWeaponSetting.smoke_check;
	Settings::Aimbot::AutoWall::enabled = currentWeaponSetting.autoWallEnabled;
	Settings::Aimbot::AutoWall::value = currentWeaponSetting.autoWallValue;

	for (int i = HITBOX_HEAD; i <= HITBOX_ARMS; i++)
		Settings::Aimbot::AutoWall::bones[i] = currentWeaponSetting.autoWallBones[i];

	Settings::Aimbot::AutoAim::real_distance = currentWeaponSetting.autoAimRealDistance;
}
