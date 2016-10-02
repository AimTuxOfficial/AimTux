#include "triggerbot.h"

bool Settings::Triggerbot::enabled = true;
ButtonCode_t Settings::Triggerbot::key = ButtonCode_t::KEY_LALT;

void Triggerbot::CreateMove(CUserCmd *cmd)
{
	if (!(Settings::Triggerbot::enabled && input->IsButtonDown(Settings::Triggerbot::key)))
		return;

	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

	Vector traceStart, traceEnd;
	QAngle viewAngles = QAngle(0.0f, 0.0f, 0.0f);

	engine->GetViewAngles(viewAngles);
	viewAngles += localplayer->GetAimPunchAngle() * 2.0f;
	Math::AngleVectors(viewAngles, traceEnd);

	traceStart = localplayer->GetVecOrigin() + localplayer->GetVecViewOffset();
	traceEnd = traceStart + (traceEnd * 8192.0f);

	Ray_t ray;
	trace_t tr;
	ray.Init(traceStart, traceEnd);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, 0x46004003, &traceFilter, &tr);

	C_BaseEntity *entity = reinterpret_cast<C_BaseEntity *>(tr.m_pEntityHit);

	if (!entity
		|| entity == localplayer
		|| entity->GetDormant()
		|| entity->GetLifeState() != LIFE_ALIVE
		|| entity->GetHealth() <= 0
		|| entity->GetTeam() == localplayer->GetTeam())
		return;

	if (!(tr.hitgroup < 10 && tr.hitgroup > 0))
		return;

	if (localplayer->GetLifeState() != LIFE_ALIVE)
		return;

	cmd->buttons |= IN_ATTACK;
}