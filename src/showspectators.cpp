#include "showspectators.h"

bool Settings::ShowSpectators::enabled = true;

std::list<int> ShowSpectators::GetObservervators(int entityId)
{
	std::list<int> list;

	if (!engine->IsInGame())
		return list;

	C_BaseEntity* pEntity = entitylist->GetClientEntity(entityId);
	if (!pEntity)
		return list;

	if (!pEntity->GetAlive())
	{
		C_BaseEntity* observerTarget = entitylist->GetClientEntityFromHandle(pEntity->GetObserverTarget());
		if (!observerTarget)
			return list;

		pEntity = observerTarget;
	}

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BaseEntity *entity = entitylist->GetClientEntity(i);
		if (!entity)
			continue;

		if (entity->GetDormant() || entity->GetAlive())
			continue;

		C_BaseEntity* target = entitylist->GetClientEntityFromHandle(entity->GetObserverTarget());
		if (pEntity != target)
			continue;

		list.push_back(i);
	}

	return list;
}