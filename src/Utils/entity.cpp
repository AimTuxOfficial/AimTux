#include "entity.h"
#include "math.h"

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
	trace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	if (smoke_check && LineGoesThroughSmoke(p_vecHead, e_vecHead, true))
		return false;

	return tr.m_pEntityHit == player;

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
	trace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	if (smoke_check && LineGoesThroughSmoke(p_vecHead, e_vecHead, true))
		return false;


	if( tr.m_pEntityHit )
	{
		if( tr.m_pEntityHit != player )
		{
			if( tr.m_pEntityHit->GetTeam() == player->GetTeam() ) // if someone from the same team
			{
				return true;
			}
		} else{
			return true;
		}
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

Bone Entity::GetBoneByName(C_BasePlayer* player, const char* boneName)
{
	studiohdr_t* pStudioModel = modelInfo->GetStudioModel(player->GetModel());
	if (!pStudioModel)
		return Bone::INVALID;

	matrix3x4_t pBoneToWorldOut[128];
	if (!player->SetupBones(pBoneToWorldOut, 128, 256, 0))
		return Bone::INVALID;

	for (int i = 0; i < pStudioModel->numbones; i++)
	{
		mstudiobone_t *pBone = pStudioModel->pBone(i);
		if (!pBone)
			continue;

		if (pBone->pszName() && strcmp(pBone->pszName(), boneName) == 0)
			return (Bone)i;
	}

	return Bone::INVALID;
}