#include "entity.h"
#include "math.h"

#include "../interfaces.h"

Vector lastRayStart;
Vector lastRayEnd;

bool Entity::IsVisible(C_BasePlayer* player, int bone, float fov, bool smoke_check)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return true;

	if (player == localplayer)
		return true;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = (C_BasePlayer*) entityList->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return true;
	}

	Vector e_vecHead = player->GetBonePosition(bone);
	Vector p_vecHead = localplayer->GetEyePosition();

	QAngle viewAngles;
	engine->GetViewAngles(viewAngles);

	// FIXME: scale fov by distance? its not really working that well...
	if (Math::GetFov(viewAngles, Math::CalcAngle(p_vecHead, e_vecHead)) > fov)
		return false;

	Ray_t ray;
	trace_t tr;
	ray.Init(p_vecHead, e_vecHead);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, MASK_VISIBLE_AND_NPCS, &traceFilter, &tr);

	if (smoke_check && LineGoesThroughSmoke(p_vecHead, e_vecHead, true))
		return false;

	return tr.m_pEntityHit == player;

}
bool Entity::IsSpotVisible(C_BasePlayer* player, Vector spot, float fov, bool smoke_check)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return true;

	if (player == localplayer)
		return true;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = (C_BasePlayer*) entityList->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return true;
	}

	Vector e_vecHead = spot;
	Vector p_vecHead = localplayer->GetEyePosition();

	QAngle viewAngles;
	engine->GetViewAngles(viewAngles);

	// FIXME: scale fov by distance? its not really working that well...
	if (Math::GetFov(viewAngles, Math::CalcAngle(p_vecHead, e_vecHead)) > fov)
		return false;

	Ray_t ray;
	trace_t tr;
	ray.Init(p_vecHead, e_vecHead);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, MASK_VISIBLE_AND_NPCS, &traceFilter, &tr);

	if (smoke_check && LineGoesThroughSmoke(p_vecHead, e_vecHead, true))
		return false;
	return (tr.m_pEntityHit==player || tr.fraction >= 0.98f);
}

bool Entity::IsVisibleThroughEnemies(C_BasePlayer *player, int bone, float fov, bool smoke_check)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return false;

	if (player == localplayer || player->GetDormant())
		return false;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = (C_BasePlayer*) entityList->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return false;
	}

	Vector e_vecHead = player->GetBonePosition(bone);
	Vector p_vecHead = localplayer->GetEyePosition();

	Ray_t ray;
	trace_t tr;
	ray.Init(p_vecHead, e_vecHead);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, MASK_VISIBLE_AND_NPCS, &traceFilter, &tr);

	if (smoke_check && LineGoesThroughSmoke(p_vecHead, e_vecHead, true))
		return false;


	if (tr.m_pEntityHit)
	{
		if (tr.m_pEntityHit != player)
		{
			if (Entity::IsTeamMate((C_BasePlayer*)tr.m_pEntityHit, player)) // if someone from the same team
				return true;
		}
		else return true;
	}
	return false;
}
bool Entity::IsSpotVisibleThroughEnemies(C_BasePlayer *player, Vector spot, float fov, bool smoke_check)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return false;

	if (player == localplayer || player->GetDormant())
		return false;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = (C_BasePlayer*) entityList->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return false;
	}

	Vector e_vecHead = spot;
	Vector p_vecHead = localplayer->GetEyePosition();

	Ray_t ray;
	trace_t tr;
	ray.Init(p_vecHead, e_vecHead);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, MASK_VISIBLE_AND_NPCS, &traceFilter, &tr);

	if (smoke_check && LineGoesThroughSmoke(p_vecHead, e_vecHead, true))
		return false;


	if (tr.m_pEntityHit)
	{
		if (tr.m_pEntityHit != player)
		{
			if (Entity::IsTeamMate((C_BasePlayer*)tr.m_pEntityHit, player)) // if someone from the same team
				return true;
		}
		else return true;
	}
	return false;
}

bool Entity::IsPlanting(C_BasePlayer* player)
{
	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*)entityList->GetClientEntityFromHandle(player->GetActiveWeapon());
	if (!activeWeapon)
		return false;

	ClientClass* clientClass = activeWeapon->GetClientClass();
	if (!clientClass)
		return false;

	if (clientClass->m_ClassID != EClassIds::CC4)
		return false;

	return ((C_WeaponC4*)activeWeapon)->GetStartedArming();
}

bool Entity::IsTeamMate(C_BasePlayer* player, C_BasePlayer* localPlayer)
{
	if (Util::IsDangerZone())
		return (localPlayer->GetSurvivalTeam() == -1) ? false : (localPlayer->GetSurvivalTeam() == player->GetSurvivalTeam());
	else
		return player->GetTeam() == localPlayer->GetTeam();
}
