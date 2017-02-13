#pragma once

#include "../SDK/SDK.h"
#include "../settings.h"
#include <algorithm>


GrenadeType getGrenadeType(C_BaseCombatWeapon* wpn);

namespace GrenadeHelper
{
	void DrawGrenadeInfo(GrenadeInfo* info);
	void DrawAimHelp(GrenadeInfo* info);
	void AimAssist(CUserCmd* cmd);
	ImColor getColor(GrenadeType type);
	void CheckForUpdate();

	void CreateMove(CUserCmd* cmd);//Activly Help to throw grenade
	void Paint();//Draw the Grenade Helper Esp
}
