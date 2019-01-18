#pragma once

#include "../SDK/IInputSystem.h"
#include "../SDK/IClientEntity.h"

GrenadeType GetGrenadeType(C_BaseCombatWeapon *wpn);

namespace GrenadeHelper
{

	//Hooks
	void CreateMove(CUserCmd* cmd);//Actively Help to throw grenade
	void PaintHybrid();//Draw the Grenade Helper Esp
}
