#include "entity.h"

bool Entity::IsVisible(C_BasePlayer* pLocal, C_BaseEntity* pEntity, int bone)
{
	Vector e_vecHead = pEntity->GetBonePosition(bone);
	Vector p_vecHead = pLocal->GetEyePosition();

	Ray_t ray;
	trace_t tr;
	ray.Init(p_vecHead, e_vecHead);
	CTraceFilter traceFilter;
	traceFilter.pSkip = pLocal;
	trace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	return tr.m_pEntityHit == pEntity;
}

std::list<std::string> Entity::GetObservervators(C_BaseEntity* pEntity)
{
	std::list<std::string> list;

	for (int i = 0; i < 64; ++i)
	{
		C_BaseEntity *entity = entitylist->GetClientEntity(i);
		if (!entity || *entity->GetObserverMode() != ObserverMode_t::OBS_MODE_IN_EYE)
			continue;

		C_BaseEntity *target = entitylist->GetClientEntityFromHandle(entity->GetObserverTarget());
		if (pEntity == target)
		{
			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(i, &entityInformation);

			list.push_back(entityInformation.name);
		}
	}

	return list;
}