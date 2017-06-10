#pragma once

#include "../SDK/SDK.h"
#include "../settings.h"
#include <algorithm>


GrenadeType GetGrenadeType(C_BaseCombatWeapon *wpn);

namespace GrenadeHelper
{
	/*
	void DrawGrenadeInfo(GrenadeInfo* info);
	void DrawAimHelp(GrenadeInfo* info);
	void AimAssist(CUserCmd* cmd);
	ImColor GetColor(GrenadeType type);
	void CheckForUpdate();
	*/

	//Hooks
	void CreateMove(CUserCmd* cmd);//Actively Help to throw grenade
	void Paint();//Draw the Grenade Helper Esp
}
