#include "showspectators.h"

bool Settings::ShowSpectators::enabled = true;

std::list<int> ShowSpectators::GetObservervators(C_BaseEntity* pEntity)
{
	std::list<int> list;

	if (!engine->IsInGame())
		return list;

	if (!pEntity || !pEntity->GetAlive())
		return list;

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BaseEntity *entity = entitylist->GetClientEntity(i);
		if (!entity)
			continue;

		if (entity->GetDormant() || entity->GetAlive())
			continue;

		C_BaseEntity *target = entitylist->GetClientEntityFromHandle(entity->GetObserverTarget());
		if (pEntity != target)
			continue;

		list.push_back(i);
	}

	return list;
}