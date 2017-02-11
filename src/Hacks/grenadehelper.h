#pragma once

#include "../SDK/SDK.h"
#include "../settings.h"

namespace GrenadeHelper
{
	bool matches(C_BaseCombatWeapon* wpn, GrenadeType type);
	void DrawGrenadeInfo(GrenadeInfo* info);
	void DrawAimHelp(GrenadeInfo* info);
	void AimAssist(CUserCmd* cmd);
	ImColor getColor(GrenadeType type);
	void CheckForUpdate();

	void CreateMove(CUserCmd* cmd);//Activly Help to throw grenade
	void Paint();//Draw the Grenade Helper Esp
}
