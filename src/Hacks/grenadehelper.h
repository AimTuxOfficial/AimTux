#pragma once

#include "../SDK/SDK.h"
#include "../settings.h"

namespace GrenadeHelper
{
	enum GrenadeType : int
	{
		FLASH,
		SMOKE,
		MOLOTOV,
		HEGRENADE
	};

	enum ThrowType : int
	{
		NORMAL,
		CROUCH,
		JUMP,
		CROUCH_JUMP
	};

	struct GrenadeInfo
	{
		GrenadeType gType;
		Vector pos;
		QAngle angle;
		ThrowType tType;
		pstring name;
		GrenadeInfo(GrenadeType gType, Vector pos, QAngle angle,ThrowType tType, pstring name)
		{
			this->gType = gType;
			this->pos = pos;
			this->angle = angle;
			this->tType = tType;
			this->name = name;
		}
	};

	bool matches(C_BaseCombatWeapon* wpn, GrenadeType type);
	void DrawGrenadeInfo(GrenadeInfo* info);
	void DrawAimHelp(GrenadeInfo* info);
	void AimAssist(CUserCmd* cmd);
	ImColor getColor(GrenadeType type);
	void CheckForUpdate();

	void CreateMove(CUserCmd* cmd);//Activly Help to throw grenade
	void Paint();//Draw the Grenade Helper Esp
}
