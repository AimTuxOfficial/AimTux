#include "entity.h"

bool Entity::IsVisible(C_BasePlayer* player, int bone)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return true;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = (C_BasePlayer*) entitylist->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return true;
	}

	Vector e_vecHead = player->GetBonePosition(bone);
	Vector p_vecHead = localplayer->GetEyePosition();

	Ray_t ray;
	trace_t tr;
	ray.Init(p_vecHead, e_vecHead);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	return tr.m_pEntityHit == player;
}

bool Entity::IsPlanting(C_BasePlayer* player)
{
	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(player->GetActiveWeapon());
	if (!active_weapon)
		return false;

	ClientClass* clientClass = active_weapon->GetClientClass();
	if (!clientClass)
		return false;

	if (clientClass->m_ClassID != CC4)
		return false;

	return ((C_WeaponC4*)active_weapon)->GetStartedArming();
}

int Entity::GetBoneByName(C_BasePlayer* player, const char* boneName)
{
	studiohdr_t* pStudioModel = modelInfo->GetStudioModel(player->GetModel());
	if (!pStudioModel)
		return -1;

	matrix3x4_t pBoneToWorldOut[128];
	if (!player->SetupBones(pBoneToWorldOut, 128, 256, 0))
		return -1;

	for (int i = 0; i < pStudioModel->numbones; i++)
	{
		mstudiobone_t *pBone = pStudioModel->pBone(i);
		if (!pBone)
			continue;

		if (pBone->pszName() && strcmp(pBone->pszName(), boneName) == 0)
			return i;
	}

	return -1;
}