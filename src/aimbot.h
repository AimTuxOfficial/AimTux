#pragma once

#include "settings.h"
#include "SDK/SDK.h"
#include "interfaces.h"
#include "entity.h"
#include "math.h"

namespace Aimbot
{
	extern bool AimStepInProgress;
	extern std::vector<int64_t> Friendlies;

	void RCS(QAngle& angle, C_BasePlayer* player, CUserCmd* cmd);
	void AimStep(C_BasePlayer* player, QAngle& angle, CUserCmd* cmd);
	void Smooth(C_BasePlayer* player, QAngle& angle, CUserCmd* cmd);
	void ConstSpeedSmooth(C_BasePlayer* player, QAngle& angle, CUserCmd* cmd);
	void AutoCrouch(C_BasePlayer* player, CUserCmd* cmd);
	void AutoStop(C_BasePlayer* player, float& forward, float& sideMove, CUserCmd* cmd);
	void AutoPistol(C_BaseCombatWeapon* active_weapon, CUserCmd* cmd);
	void AutoShoot(C_BasePlayer* player, C_BaseCombatWeapon* active_weapon, CUserCmd* cmd);
	void ShootCheck(C_BaseCombatWeapon* active_weapon, CUserCmd* cmd);
	void NoShoot(C_BaseCombatWeapon* active_weapon, C_BasePlayer* player, CUserCmd* cmd);

	void CreateMove(CUserCmd* cmd);
	void FireEventClientSide(IGameEvent* event);
}
