#include "aimbot.h"
#include "autowall.h"
#include "../interfaces.h"
#include <math.h>

// Default aimbot settings
bool Settings::Aimbot::enabled = false;
bool Settings::Aimbot::silent = false;
bool Settings::Aimbot::friendly = false;
Bone Settings::Aimbot::bone = Bone::BONE_HEAD;
ButtonCode_t Settings::Aimbot::aimkey = ButtonCode_t::MOUSE_MIDDLE;
bool Settings::Aimbot::aimkeyOnly = false;
bool Settings::Aimbot::Smooth::enabled = false;
float Settings::Aimbot::Smooth::value = 0.5f;
SmoothType Settings::Aimbot::Smooth::type = SmoothType::SLOW_END;
bool Settings::Aimbot::ErrorMargin::enabled = false;
float Settings::Aimbot::ErrorMargin::value = 0.0f;
bool Settings::Aimbot::AutoAim::enabled = false;
float Settings::Aimbot::AutoAim::fov = 180.0f;
bool Settings::Aimbot::AutoAim::realDistance = false;
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
float Settings::Aimbot::RCS::valueX = 2.0f;
float Settings::Aimbot::RCS::valueY = 2.0f;
bool Settings::Aimbot::AutoCrouch::enabled = false;
bool Settings::Aimbot::NoShoot::enabled = false;
bool Settings::Aimbot::IgnoreJump::enabled = false;
bool Settings::Aimbot::SmokeCheck::enabled = false;
bool Settings::Aimbot::FlashCheck::enabled = false;
bool Settings::Aimbot::Smooth::Salting::enabled = false;
float Settings::Aimbot::Smooth::Salting::multiplier = 0.0f;
bool Settings::Aimbot::AutoSlow::enabled = false;
float Settings::Aimbot::AutoSlow::minDamage = 5.0f;
bool Settings::Aimbot::Prediction::enabled = false;

bool Aimbot::aimStepInProgress = false;
std::vector<int64_t> Aimbot::friends = { };

bool shouldAim;
QAngle AimStepLastAngle;
QAngle RCSLastPunch;

std::unordered_map<Hitbox, std::vector<const char*>, Util::IntHash<Hitbox>> hitboxes = {
		{ Hitbox::HITBOX_HEAD, { "head_0" } },
		{ Hitbox::HITBOX_NECK, { "neck_0" } },
		{ Hitbox::HITBOX_PELVIS, { "pelvis" } },
		{ Hitbox::HITBOX_SPINE, { "spine_0", "spine_1", "spine_2", "spine_3" } },
		{ Hitbox::HITBOX_LEGS, { "leg_upper_L", "leg_upper_R", "leg_lower_L", "leg_lower_R", "ankle_L", "ankle_R" } },
		{ Hitbox::HITBOX_ARMS, { "hand_L", "hand_R", "arm_upper_L", "arm_lower_L", "arm_upper_R", "arm_lower_R" } },
};

std::unordered_map<ItemDefinitionIndex, AimbotWeapon_t, Util::IntHash<ItemDefinitionIndex>> Settings::Aimbot::weapons = {
		{ ItemDefinitionIndex::INVALID, { false, false, false, Bone::BONE_HEAD, ButtonCode_t::MOUSE_MIDDLE, false, false, 1.0f, SmoothType::SLOW_END, false, 0.0f, false, 0.0f, true, 180.0f, false, 25.0f, false, false, 2.0f, 2.0f, false, false, false, false, false, false, false, false, 10.0f, false, false, false, 5.0f } },
};

static const char* targets[] = { "pelvis", "", "", "spine_0", "spine_1", "spine_2", "spine_3", "neck_0", "head_0" };

static void ApplyErrorToAngle(QAngle* angles, float margin)
{
	QAngle error;
	error.Random(-1.0f, 1.0f);
	error *= margin;
	angles->operator+=(error);
}

void GetBestBone(C_BasePlayer* player, float& bestDamage, Bone& bestBone)
{
	bestBone = Bone::BONE_HEAD;

	for (std::unordered_map<Hitbox, std::vector<const char*>, Util::IntHash<Hitbox>>::iterator it = hitboxes.begin(); it != hitboxes.end(); it++)
	{
		if (!Settings::Aimbot::AutoWall::bones[(int) it->first])
			continue;

		std::vector<const char*> hitboxList = hitboxes[it->first];
		for (std::vector<const char*>::iterator it2 = hitboxList.begin(); it2 != hitboxList.end(); it2++)
		{
			Bone bone = Entity::GetBoneByName(player, *it2);
			Vector vecBone = player->GetBonePosition((int) bone);

			Autowall::FireBulletData data;
			float damage = Autowall::GetDamage(vecBone, !Settings::Aimbot::friendly, data);

			if (damage > bestDamage)
			{
				bestDamage = damage;
				bestBone = bone;
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

	return aimingAt.DistTo(aimAt);
}

Vector VelocityExtrapolate(C_BasePlayer* player, Vector aimPos)
{
	return aimPos + (player->GetVelocity() * globalVars->interval_per_tick);
}

C_BasePlayer* GetClosestPlayer(CUserCmd* cmd, bool visible, Bone& bestBone, float& bestDamage, AimTargetType aimTargetType = AimTargetType::FOV)
{
	if (Settings::Aimbot::AutoAim::realDistance)
		aimTargetType = AimTargetType::REAL_DISTANCE;

	bestBone = static_cast<Bone>(Settings::Aimbot::bone);

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	C_BasePlayer* closestEntity = NULL;

	// TODO Change the big value with a distance/fov slider
	float bestFov = Settings::Aimbot::AutoAim::fov;
	float bestRealDistance = Settings::Aimbot::AutoAim::fov * 5.f;
	float bestDistance = 999999999.0f;
	int bestHp = 100;

	if (!localplayer)
		return NULL;

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BasePlayer* player = (C_BasePlayer*) entityList->GetClientEntity(i);

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

		if (std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid) != Aimbot::friends.end())
			continue;

		Vector eVecTarget = player->GetBonePosition((int) Settings::Aimbot::bone);
		Vector pVecTarget = localplayer->GetEyePosition();

		QAngle viewAngles;
		engine->GetViewAngles(viewAngles);

		float distance = pVecTarget.DistTo(eVecTarget);
		float fov = Math::GetFov(viewAngles, Math::CalcAngle(pVecTarget, eVecTarget));
		float real_distance = GetRealDistanceFOV(distance, Math::CalcAngle(pVecTarget, eVecTarget), cmd);
		int hp = player->GetHealth();

		if (aimTargetType == AimTargetType::DISTANCE && distance > bestDistance)
			continue;

		if (aimTargetType == AimTargetType::FOV && fov > bestFov)
			continue;

		if (aimTargetType == AimTargetType::REAL_DISTANCE && real_distance > bestRealDistance)
			continue;

		if (aimTargetType == AimTargetType::HP && hp > bestHp)
			continue;

		if (visible && !Settings::Aimbot::AutoWall::enabled && !Entity::IsVisible(player, Settings::Aimbot::bone))
			continue;

		bestBone = static_cast<Bone>(Entity::GetBoneByName(player, targets[(int) Settings::Aimbot::bone]));

		if (Settings::Aimbot::AutoWall::enabled)
		{
			float damage = 0.0f;
			Bone bone;
			GetBestBone(player, damage, bone);

			if (damage >= bestDamage && damage >= Settings::Aimbot::AutoWall::value)
			{
				bestDamage = damage;
				bestBone = bone;
				closestEntity = player;
			}
		}
		else
		{
			closestEntity = player;
			bestFov = fov;
			bestRealDistance = real_distance;
			bestDistance = distance;
			bestHp = hp;
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

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	QAngle CurrentPunch = *localplayer->GetAimPunchAngle();
	bool isSilent = Settings::Aimbot::silent;
	bool hasTarget = Settings::Aimbot::AutoAim::enabled && player && shouldAim;

	if (!Settings::Aimbot::RCS::always_on && !hasTarget)
		return;

	if (isSilent || hasTarget)
	{
		angle.x -= CurrentPunch.x * Settings::Aimbot::RCS::valueX;
		angle.y -= CurrentPunch.y * Settings::Aimbot::RCS::valueY;
	}
	else if (localplayer->GetShotsFired() > 1)
	{
		QAngle NewPunch = { CurrentPunch.x - RCSLastPunch.x, CurrentPunch.y - RCSLastPunch.y, 0 };

		angle.x -= NewPunch.x * Settings::Aimbot::RCS::valueX;
		angle.y -= NewPunch.y * Settings::Aimbot::RCS::valueY;
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

	if (!Aimbot::aimStepInProgress)
		AimStepLastAngle = cmd->viewangles;

	if (!player)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	Vector eVecTarget = player->GetBonePosition((int) Settings::Aimbot::bone);
	Vector pVecTarget = localplayer->GetEyePosition();
	float fov = Math::GetFov(AimStepLastAngle, Math::CalcAngle(pVecTarget, eVecTarget));

	Aimbot::aimStepInProgress = fov > Settings::Aimbot::AimStep::value;

	if (!Aimbot::aimStepInProgress)
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
	float sine = sin (globalVars->tickcount);
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
		Salt(smooth);

	QAngle toChange = QAngle();

	int type = (int) Settings::Aimbot::Smooth::type;

	if (type == (int) SmoothType::SLOW_END)
		toChange = delta - delta * smooth;
	else if (type == (int) SmoothType::CONSTANT || type == (int) SmoothType::FAST_END)
	{
		float coeff = (1.0f - smooth) / delta.Length() * 4.f;

		if (type == (int) SmoothType::FAST_END)
			coeff = powf(coeff, 2.f) * 10.f;

		coeff = std::min(1.f, coeff);
		toChange = delta * coeff;
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

void Aimbot::AutoSlow(C_BasePlayer* player, float& forward, float& sideMove, float& bestDamage, C_BaseCombatWeapon* active_weapon, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoWall::enabled)
		return;

	if (!Settings::Aimbot::AutoSlow::enabled)
		return;

	if (!player)
		return;

	float nextPrimaryAttack = active_weapon->GetNextPrimaryAttack();

	if (nextPrimaryAttack > globalVars->curtime)
		return;

	if (bestDamage > Settings::Aimbot::AutoSlow::minDamage)
	{
		forward *= 0.2f;
		sideMove *= 0.16f;
		cmd->upmove = 0;
	}
}

void Aimbot::AutoPistol(C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoPistol::enabled)
		return;

	if (!activeWeapon || activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_PISTOL)
		return;

	if (activeWeapon->GetNextPrimaryAttack() < globalVars->curtime)
		return;

	if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
		cmd->buttons &= ~IN_ATTACK2;
	else
		cmd->buttons &= ~IN_ATTACK;
}

void Aimbot::AutoShoot(C_BasePlayer* player, C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)
{
	if (!Settings::Aimbot::AutoShoot::enabled)
		return;

	if (Settings::Aimbot::AimStep::enabled && Aimbot::aimStepInProgress)
		return;

	if (!player || !activeWeapon || activeWeapon->GetAmmo() == 0)
		return;

	CSWeaponType weaponType = activeWeapon->GetCSWpnData()->GetWeaponType();
	if (weaponType == CSWeaponType::WEAPONTYPE_KNIFE || weaponType == CSWeaponType::WEAPONTYPE_C4 || weaponType == CSWeaponType::WEAPONTYPE_GRENADE)
		return;

	if (cmd->buttons & IN_USE)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	float nextPrimaryAttack = activeWeapon->GetNextPrimaryAttack();

	if (nextPrimaryAttack > globalVars->curtime)
	{
		if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
			cmd->buttons &= ~IN_ATTACK2;
		else
			cmd->buttons &= ~IN_ATTACK;
	}
	else
	{
		if (Settings::Aimbot::AutoShoot::autoscope && activeWeapon->GetCSWpnData()->GetZoomLevels() > 0 && !localplayer->IsScoped())
			cmd->buttons |= IN_ATTACK2;
		else if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
			cmd->buttons |= IN_ATTACK2;
		else
			cmd->buttons |= IN_ATTACK;
	}
}

void Aimbot::ShootCheck(C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)
{
	if (!Settings::AntiAim::Pitch::enabled && !Settings::AntiAim::Yaw::enabled)
		return;

	if (!Settings::Aimbot::silent)
		return;

	if (!(cmd->buttons & IN_ATTACK))
		return;

	if (activeWeapon->GetNextPrimaryAttack() < globalVars->curtime)
		return;

	if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_C4)
		return;

	if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
		cmd->buttons &= ~IN_ATTACK2;
	else
		cmd->buttons &= ~IN_ATTACK;
}

void Aimbot::NoShoot(C_BaseCombatWeapon* activeWeapon, C_BasePlayer* player, CUserCmd* cmd)
{
	if (player && Settings::Aimbot::NoShoot::enabled)
	{
		if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_C4)
			return;

		if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
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

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if (Settings::Aimbot::IgnoreJump::enabled && !(localplayer->GetFlags() & FL_ONGROUND))
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!activeWeapon || activeWeapon->GetInReload())
		return;

	CSWeaponType weaponType = activeWeapon->GetCSWpnData()->GetWeaponType();
	if (weaponType == CSWeaponType::WEAPONTYPE_C4 || weaponType == CSWeaponType::WEAPONTYPE_GRENADE || weaponType == CSWeaponType::WEAPONTYPE_KNIFE)
		return;

	Bone aw_bone;
	float bestDamage = 0.0f;
	C_BasePlayer* player = GetClosestPlayer(cmd, true, aw_bone, bestDamage);

	if (player)
	{
		bool skipPlayer = false;

		Vector eVecTarget = player->GetBonePosition((int) aw_bone);
		Vector pVecTarget = localplayer->GetEyePosition();

		if (Settings::Aimbot::SmokeCheck::enabled && LineGoesThroughSmoke(pVecTarget, eVecTarget, true))
			skipPlayer = true;

		if (Settings::Aimbot::FlashCheck::enabled && localplayer->GetFlashBangTime() - globalVars->curtime > 2.0f)
			skipPlayer = true;

		if (skipPlayer)
			player = nullptr;

		if (Settings::Aimbot::AutoAim::enabled && !skipPlayer)
		{
			if (cmd->buttons & IN_ATTACK && !Settings::Aimbot::aimkeyOnly)
				shouldAim = true;

			if (inputSystem->IsButtonDown(Settings::Aimbot::aimkey))
				shouldAim = true;

			if (shouldAim)
			{
				if (Settings::Aimbot::Prediction::enabled)
				{
					pVecTarget = VelocityExtrapolate(localplayer, pVecTarget); // get eye pos next tick
					eVecTarget = VelocityExtrapolate(player, eVecTarget); // get target pos next tick
				}
				angle = Math::CalcAngle(pVecTarget, eVecTarget);

				if (Settings::Aimbot::ErrorMargin::enabled)
					ApplyErrorToAngle(&angle, Settings::Aimbot::ErrorMargin::value);
			}
		}
	}

	Aimbot::AimStep(player, angle, cmd);
	Aimbot::AutoCrouch(player, cmd);
	Aimbot::AutoSlow(player, oldForward, oldSideMove, bestDamage, activeWeapon, cmd);
	Aimbot::AutoPistol(activeWeapon, cmd);
	Aimbot::AutoShoot(player, activeWeapon, cmd);
	Aimbot::RCS(angle, player, cmd);
	Aimbot::Smooth(player, angle, cmd);
	Aimbot::ShootCheck(activeWeapon, cmd);
	Aimbot::NoShoot(activeWeapon, player, cmd);

	Math::NormalizeAngles(angle);
	Math::ClampAngles(angle);

	if (angle != cmd->viewangles)
		cmd->viewangles = angle;

	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);

	if (!Settings::Aimbot::silent)
		engine->SetViewAngles(cmd->viewangles);
}

void Aimbot::FireGameEvent(IGameEvent* event)
{
	if (!event)
		return;

	if (strcmp(event->GetName(), "player_connect_full") != 0 && strcmp(event->GetName(), "cs_game_disconnected") != 0)
		return;

	if (event->GetInt("userid") && engine->GetPlayerForUserID(event->GetInt("userid")) != engine->GetLocalPlayer())
		return;

	Aimbot::friends.clear();
}

void Aimbot::UpdateValues()
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!activeWeapon)
		return;

	ItemDefinitionIndex index = ItemDefinitionIndex::INVALID;
	if (Settings::Aimbot::weapons.find(*activeWeapon->GetItemDefinitionIndex()) != Settings::Aimbot::weapons.end())
		index = *activeWeapon->GetItemDefinitionIndex();

	const AimbotWeapon_t& currentWeaponSetting = Settings::Aimbot::weapons.at(index);

	Settings::Aimbot::enabled = currentWeaponSetting.enabled;
	Settings::Aimbot::silent = currentWeaponSetting.silent;
	Settings::Aimbot::friendly = currentWeaponSetting.friendly;
	Settings::Aimbot::bone = currentWeaponSetting.bone;
	Settings::Aimbot::aimkey = currentWeaponSetting.aimkey;
	Settings::Aimbot::aimkeyOnly = currentWeaponSetting.aimkeyOnly;
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
	Settings::Aimbot::RCS::always_on = currentWeaponSetting.rcsAlwaysOn;
	Settings::Aimbot::RCS::valueX = currentWeaponSetting.rcsAmountX;
	Settings::Aimbot::RCS::valueY = currentWeaponSetting.rcsAmountY;
	Settings::Aimbot::NoShoot::enabled = currentWeaponSetting.noShootEnabled;
	Settings::Aimbot::IgnoreJump::enabled = currentWeaponSetting.ignoreJumpEnabled;
	Settings::Aimbot::Smooth::Salting::enabled = currentWeaponSetting.smoothSaltEnabled;
	Settings::Aimbot::Smooth::Salting::multiplier = currentWeaponSetting.smoothSaltMultiplier;
	Settings::Aimbot::SmokeCheck::enabled = currentWeaponSetting.smokeCheck;
	Settings::Aimbot::FlashCheck::enabled = currentWeaponSetting.flashCheck;
	Settings::Aimbot::AutoWall::enabled = currentWeaponSetting.autoWallEnabled;
	Settings::Aimbot::AutoWall::value = currentWeaponSetting.autoWallValue;
	Settings::Aimbot::AutoSlow::enabled = currentWeaponSetting.autoSlow;
	Settings::Aimbot::AutoSlow::minDamage = currentWeaponSetting.autoSlowMinDamage;

	for (int i = (int) Hitbox::HITBOX_HEAD; i <= (int) Hitbox::HITBOX_ARMS; i++)
		Settings::Aimbot::AutoWall::bones[i] = currentWeaponSetting.autoWallBones[i];

	Settings::Aimbot::AutoAim::realDistance = currentWeaponSetting.autoAimRealDistance;
}
