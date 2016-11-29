#include "triggerbot.h"

bool Settings::Triggerbot::enabled = true;
bool Settings::Triggerbot::Filter::friendly = false;
bool Settings::Triggerbot::Filter::head = true;
bool Settings::Triggerbot::Filter::chest = true;
bool Settings::Triggerbot::Filter::stomach = true;
bool Settings::Triggerbot::Filter::arms = true;
bool Settings::Triggerbot::Filter::legs = true;
bool Settings::Triggerbot::Delay::enabled = false;
int Settings::Triggerbot::Delay::value = 250;
ButtonCode_t Settings::Triggerbot::key = ButtonCode_t::KEY_LALT;

void Triggerbot::CreateMove(CUserCmd *cmd)
{
	if (!Settings::Triggerbot::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (!input->IsButtonDown(Settings::Triggerbot::key))
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	static long timeStamp = currentTime_ms;
	long oldTimeStamp;

	Vector traceStart, traceEnd;
	QAngle viewAngles = QAngle(0.0f, 0.0f, 0.0f);

	engine->GetViewAngles(viewAngles);
	viewAngles += localplayer->GetAimPunchAngle() * 2.0f;
	Math::AngleVectors(viewAngles, traceEnd);

	traceStart = localplayer->GetEyePosition();
	traceEnd = traceStart + (traceEnd * 8192.0f);

	Ray_t ray;
	trace_t tr;
	ray.Init(traceStart, traceEnd);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, 0x46004003, &traceFilter, &tr);

	oldTimeStamp = timeStamp;
	timeStamp = currentTime_ms;

	C_BaseEntity *entity = tr.m_pEntityHit;
	if (!entity)
		return;

	if (entity->GetClientClass()->m_ClassID != CCSPlayer)
		return;

	if (entity == localplayer
		|| entity->GetDormant()
		|| !entity->GetAlive())
		return;

	if (entity->GetTeam() == localplayer->GetTeam() && !Settings::Triggerbot::Filter::friendly)
		return;
	else if (tr.hitgroup == HitGroups::HITGROUP_HEAD && !Settings::Triggerbot::Filter::head)
		return;
	else if (tr.hitgroup == HitGroups::HITGROUP_CHEST && !Settings::Triggerbot::Filter::chest)
		return;
	else if (tr.hitgroup == HitGroups::HITGROUP_STOMACH && !Settings::Triggerbot::Filter::stomach)
		return;
	else if ((tr.hitgroup == HitGroups::HITGROUP_LEFTARM || tr.hitgroup == HitGroups::HITGROUP_RIGHTARM) && !Settings::Triggerbot::Filter::arms)
		return;
	else if ((tr.hitgroup == HitGroups::HITGROUP_LEFTLEG || tr.hitgroup == HitGroups::HITGROUP_RIGHTLEG) && !Settings::Triggerbot::Filter::legs)
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon)
		return;

	timeStamp = oldTimeStamp;

	if (active_weapon->IsKnife() || active_weapon->GetAmmo() == 0)
		return;

	float nextPrimaryAttack = active_weapon->GetNextPrimaryAttack();
	float tick = localplayer->GetTickBase() * globalvars->interval_per_tick;

	if (nextPrimaryAttack > tick)
	{
		if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			cmd->buttons &= ~IN_ATTACK2;
		else
			cmd->buttons &= ~IN_ATTACK;
	}
	else
	{
		if (Settings::Triggerbot::Delay::enabled && currentTime_ms - timeStamp < Settings::Triggerbot::Delay::value)
			return;

		if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			cmd->buttons |= IN_ATTACK2;
		else
			cmd->buttons |= IN_ATTACK;
	}

	timeStamp = currentTime_ms;
}