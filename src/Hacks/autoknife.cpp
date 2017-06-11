#include "autoknife.h"

bool Settings::AutoKnife::enabled = false;
bool Settings::AutoKnife::Filters::enemies = true;
bool Settings::AutoKnife::Filters::allies = false;
bool Settings::AutoKnife::onKey = true;

bool AutoKnife::IsPlayerBehind(C_BasePlayer* localplayer, C_BasePlayer* player)
{
	Vector toTarget = (localplayer->GetVecOrigin() - player->GetVecOrigin()).Normalize();
	Vector playerViewAngles;
	Math::AngleVectors(*player->GetEyeAngles(), playerViewAngles);
	if (toTarget.Dot(playerViewAngles) > -0.5f)
		return false;
	else
		return true;
}

int AutoKnife::GetKnifeDamageDone(C_BasePlayer* localplayer, C_BasePlayer* player)
{
	//damage: unarmored/armored
	//leftclick: 39/33
	//rightclick: 55/65
	//backstab leftclick: 90/76
	//backstab rightclick: 180/153
	bool backstab = IsPlayerBehind(localplayer, player);
	int armor = player->GetArmor();
	if (!backstab)
	{
		if (armor>0)
			return 33; // 21
		else
			return 39; // 25
	}
	else
	{
		if (armor>0)
			return 76; // 76
		else
			return 90; // 90
	}
}

int AutoKnife::GetKnife2DamageDone(C_BasePlayer* localplayer, C_BasePlayer* player)
{
	//damage: unarmored/armored
	//leftclick: 39/33
	//rightclick: 55/65
	//backstab leftclick: 90/76
	//backstab rightclick: 180/153
	bool backstab = IsPlayerBehind(localplayer, player);
	int armor = player->GetArmor();
	if (!backstab)
	{
		if (armor>0)
			return 55;
		else
			return 65;
	}
	else
	{
		return 100;
	}
}

void AutoKnife::CreateMove(CUserCmd *cmd)
{
	if (!engine->IsInGame())
		return;

	if (!Settings::AutoKnife::enabled)
		return;

	if (!inputSystem->IsButtonDown(Settings::Triggerbot::key) && Settings::AutoKnife::onKey)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!activeWeapon)
		return;

	ItemDefinitionIndex itemDefinitionIndex = *activeWeapon->GetItemDefinitionIndex();
	if (!Util::Items::IsKnife(itemDefinitionIndex) && itemDefinitionIndex != ItemDefinitionIndex::WEAPON_TASER)
		return;

	if (itemDefinitionIndex == ItemDefinitionIndex::WEAPON_TASER && activeWeapon->GetAmmo() == 0)
		return;

	Vector traceStart, traceEnd;
	trace_t tr;

	QAngle viewAngles;
	engine->GetViewAngles(viewAngles);
	QAngle viewAnglesRcs = viewAngles + *localplayer->GetAimPunchAngle() * 2.0f;

	Math::AngleVectors(viewAnglesRcs, traceEnd);

	traceStart = localplayer->GetEyePosition();
	traceEnd = traceStart + (traceEnd * 8192.0f);
	
	Ray_t ray;
	ray.Init(traceStart, traceEnd);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, 0x46004003, &traceFilter, &tr);

	C_BasePlayer* player = (C_BasePlayer*) tr.m_pEntityHit;
	if (!player)
		return;

	if (player->GetClientClass()->m_ClassID != EClassIds::CCSPlayer)
		return;

	if (player == localplayer
		|| player->GetDormant()
		|| !player->GetAlive()
		|| player->GetImmune())
		return;

	if (player->GetTeam() != localplayer->GetTeam() && !Settings::AutoKnife::Filters::enemies)
		return;

	if (player->GetTeam() == localplayer->GetTeam() && !Settings::AutoKnife::Filters::allies)
		return;

	float playerDistance = localplayer->GetVecOrigin().DistTo(player->GetVecOrigin());
	if (activeWeapon->GetNextPrimaryAttack() < globalVars->curtime)
	{
		if (itemDefinitionIndex == ItemDefinitionIndex::WEAPON_TASER)
		{
			if (playerDistance <= 184.f)
				cmd->buttons |= IN_ATTACK;
		}
		else
		{
			if (playerDistance <= 65.f && GetKnife2DamageDone(localplayer, player) >= player->GetHealth())
				cmd->buttons |= IN_ATTACK2;
			else if (IsPlayerBehind(localplayer, player) && playerDistance <= 65.f)
				cmd->buttons |= IN_ATTACK2;
			else if (playerDistance <= 78.f)
			{
				if (IsPlayerBehind(localplayer, player))
					return;

				if (playerDistance <= 65.f &&
					(2*(GetKnifeDamageDone(localplayer, player)) + GetKnife2DamageDone(localplayer, player) - 13) < player->GetHealth())
					cmd->buttons |= IN_ATTACK2;
				else
					cmd->buttons |= IN_ATTACK;
			}
		}
	}
}
