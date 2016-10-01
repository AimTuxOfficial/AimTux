#include "triggerbot.h"

bool Settings::Triggerbot::enabled = true;
ButtonCode_t Settings::Triggerbot::key = ButtonCode_t::KEY_LALT;

void inline Triggerbot::SinCos( float radians, float *sine, float *cosine )
{
	register double __cosr, __sinr;
	__asm ("fsincos" : "=t" (__cosr), "=u" (__sinr) : "0" (radians));

	*sine = __sinr;
	*cosine = __cosr;
}

void Triggerbot::AngleVectors (const QAngle &angles, Vector& forward) {
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float sp, sy, cp, cy;

	Triggerbot::SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	Triggerbot::SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

void Triggerbot::CreateMove(CUserCmd *cmd)
{
	if (Settings::Triggerbot::enabled && input->IsButtonDown(Settings::Triggerbot::key)) {
		C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

		Vector traceStart, traceEnd;
		QAngle viewAngles = QAngle(0.0f, 0.0f, 0.0f);

		engine->GetViewAngles(viewAngles);
		viewAngles += localplayer->GetAimPunchAngle() * 2.0f;
		AngleVectors(viewAngles, traceEnd);

		traceStart = localplayer->GetVecOrigin() + localplayer->GetVecViewOffset();
		traceEnd = traceStart + (traceEnd * 8192.0f);

		Ray_t ray;
		trace_t tr;
		ray.Init(traceStart, traceEnd);
		CTraceFilter traceFilter;
		traceFilter.pSkip = localplayer;
		trace->TraceRay(ray, 0x46004003, &traceFilter, &tr);

		C_BaseEntity *entity = reinterpret_cast<C_BaseEntity *>(tr.m_pEntityHit);
		C_BaseCombatWeapon *active_weapon = reinterpret_cast<C_BaseCombatWeapon *>(localplayer->GetActiveWeapon());

		if (!entity
			|| entity == localplayer
			|| entity->GetDormant()
			|| entity->GetLifeState() != LIFE_ALIVE
			|| entity->GetHealth() <= 0
			|| entity->GetTeam() == localplayer->GetTeam())
			return;

		if (!(tr.hitgroup < 10 && tr.hitgroup > 0))
			return;

		if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			cmd->buttons |= IN_ATTACK2;
		else
			cmd->buttons |= IN_ATTACK;
	}
}