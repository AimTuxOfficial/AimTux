#include "triggerbot.h"
#include "autowall.h"

bool Settings::Triggerbot::enabled = false;
bool Settings::Triggerbot::Filters::enemies = true;
bool Settings::Triggerbot::Filters::allies = false;
bool Settings::Triggerbot::Filters::walls = false;
bool Settings::Triggerbot::Filters::smokeCheck = false;
bool Settings::Triggerbot::Filters::flashCheck = false;
bool Settings::Triggerbot::Filters::head = true;
bool Settings::Triggerbot::Filters::chest = true;
bool Settings::Triggerbot::Filters::stomach = true;
bool Settings::Triggerbot::Filters::arms = true;
bool Settings::Triggerbot::Filters::legs = true;
bool Settings::Triggerbot::Delay::enabled = false;
int Settings::Triggerbot::Delay::value = 250;
ButtonCode_t Settings::Triggerbot::key = ButtonCode_t::KEY_LALT;

void Triggerbot::CreateMove(CUserCmd *cmd)
{
	if (!Settings::Triggerbot::enabled)
		return;

	if (!inputSystem->IsButtonDown(Settings::Triggerbot::key))
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;
	
	if (Settings::Triggerbot::Filters::flashCheck && localplayer->GetFlashBangTime() - globalVars->curtime > 2.0f)
		return;

	long currentTime_ms = Util::GetEpochTime();
	static long timeStamp = currentTime_ms;
	long oldTimeStamp;

	Vector traceStart, traceEnd;
	trace_t tr;

	QAngle viewAngles;
	engine->GetViewAngles(viewAngles);
	QAngle viewAngles_rcs = viewAngles + *localplayer->GetAimPunchAngle() * 2.0f;

	Math::AngleVectors(viewAngles_rcs, traceEnd);

	traceStart = localplayer->GetEyePosition();
	traceEnd = traceStart + (traceEnd * 8192.0f);

	if (Settings::Triggerbot::Filters::walls)
	{
		Autowall::FireBulletData data;
		if (Autowall::GetDamage(traceEnd, !Settings::Triggerbot::Filters::allies, data) == 0.0f)
			return;

		tr = data.enter_trace;
	}
	else
	{
		Ray_t ray;
		ray.Init(traceStart, traceEnd);
		CTraceFilter traceFilter;
		traceFilter.pSkip = localplayer;
		trace->TraceRay(ray, 0x46004003, &traceFilter, &tr);
	}

	oldTimeStamp = timeStamp;
	timeStamp = currentTime_ms;

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

	if (player->GetTeam() != localplayer->GetTeam() && !Settings::Triggerbot::Filters::enemies)
		return;

	if (player->GetTeam() == localplayer->GetTeam() && !Settings::Triggerbot::Filters::allies)
		return;

	bool filter;

	switch (tr.hitgroup)
	{
		case HitGroups::HITGROUP_HEAD:
			filter = Settings::Triggerbot::Filters::head;
			break;
		case HitGroups::HITGROUP_CHEST:
			filter = Settings::Triggerbot::Filters::chest;
			break;
		case HitGroups::HITGROUP_STOMACH:
			filter = Settings::Triggerbot::Filters::stomach;
			break;
		case HitGroups::HITGROUP_LEFTARM:
		case HitGroups::HITGROUP_RIGHTARM:
			filter = Settings::Triggerbot::Filters::arms;
			break;
		case HitGroups::HITGROUP_LEFTLEG:
		case HitGroups::HITGROUP_RIGHTLEG:
			filter = Settings::Triggerbot::Filters::legs;
			break;
		default:
			filter = false;
	}

	if (!filter)
		return;

	if (Settings::Triggerbot::Filters::smokeCheck && LineGoesThroughSmoke(tr.startpos, tr.endpos, 1))
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!activeWeapon || activeWeapon->GetAmmo() == 0)
		return;

	ItemDefinitionIndex itemDefinitionIndex = *activeWeapon->GetItemDefinitionIndex();
	if (itemDefinitionIndex == ItemDefinitionIndex::WEAPON_KNIFE || itemDefinitionIndex >= ItemDefinitionIndex::WEAPON_KNIFE_BAYONET)
		return;

	CSWeaponType weaponType = activeWeapon->GetCSWpnData()->GetWeaponType();
	if (weaponType == CSWeaponType::WEAPONTYPE_C4 || weaponType == CSWeaponType::WEAPONTYPE_GRENADE)
		return;

	if (activeWeapon->GetNextPrimaryAttack() > globalVars->curtime)
	{
		if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
			cmd->buttons &= ~IN_ATTACK2;
		else
			cmd->buttons &= ~IN_ATTACK;
	}
	else
	{
		if (Settings::Triggerbot::Delay::enabled && currentTime_ms - oldTimeStamp < Settings::Triggerbot::Delay::value)
		{
			timeStamp = oldTimeStamp;
			return;
		}

		if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
			cmd->buttons |= IN_ATTACK2;
		else
			cmd->buttons |= IN_ATTACK;
	}

	timeStamp = currentTime_ms;
}
