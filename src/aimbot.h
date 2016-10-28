#pragma once

#include "settings.h"
#include "SDK/SDK.h"
#include "interfaces.h"
#include "entity.h"
#include "math.h"

namespace Aimbot
{
	extern bool AimStepInProgress;

	void RCS(QAngle& angle, C_BaseEntity* entity, CUserCmd* cmd);
	void AimStep(C_BaseEntity* entity, QAngle& angle, CUserCmd* cmd);
	void Smooth(C_BaseEntity* entity, QAngle& angle, CUserCmd* cmd);
	void AutoCrouch(C_BaseEntity* entity, CUserCmd* cmd);
	void AutoStop(C_BaseEntity* entity, float& forward, float& sideMove, CUserCmd* cmd);
	void AutoPistol(C_BaseCombatWeapon* active_weapon, CUserCmd* cmd);
	void AutoShoot(C_BaseEntity* entity, C_BaseCombatWeapon* active_weapon, CUserCmd* cmd);
	void ShootCheck(C_BaseCombatWeapon* active_weapon, CUserCmd* cmd);

	void CreateMove(CUserCmd* cmd);
}