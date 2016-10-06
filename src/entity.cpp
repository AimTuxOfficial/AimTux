#include "entity.h"

bool Entity::IsVisible(C_BasePlayer* pLocal, C_BaseEntity* pEntity, int bone)
{
	Vector e_vecHead = GetBone(pEntity, bone);
	Vector p_vecHead = pLocal->GetVecOrigin() + pLocal->GetVecViewOffset();

	Ray_t ray;
	trace_t tr;
	ray.Init(p_vecHead, e_vecHead);
	CTraceFilter traceFilter;
	traceFilter.pSkip = pLocal;
	trace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	return tr.m_pEntityHit == pEntity;
}