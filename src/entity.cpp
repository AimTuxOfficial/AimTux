#include "entity.h"

bool Entity::IsVisible(C_BaseEntity* pEntity, int bone)
{
	C_BaseEntity* localplayer = entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return true;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = entitylist->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return true;
	}

	Vector e_vecHead = pEntity->GetBonePosition(bone);
	Vector p_vecHead = localplayer->GetEyePosition();

	Ray_t ray;
	trace_t tr;
	ray.Init(p_vecHead, e_vecHead);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	return tr.m_pEntityHit == pEntity;
}

int Entity::GetBoneByName(C_BaseEntity *pEntity, const char* boneName)
{
	studiohdr_t* pStudioModel = modelInfo->GetStudioModel(pEntity->GetModel());
	if (!pStudioModel)
		return -1;

	matrix3x4_t pBoneToWorldOut[128];
	if (!pEntity->SetupBones(pBoneToWorldOut, 128, 256, 0))
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