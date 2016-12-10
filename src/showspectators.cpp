#include "showspectators.h"

bool Settings::ShowSpectators::enabled = true;

std::list<std::string> ShowSpectators::GetObservervators(C_BaseEntity* pEntity)
{
	std::list<std::string> list;

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

		if (*entity->GetObserverMode() != ObserverMode_t::OBS_MODE_IN_EYE)
			continue;

		C_BaseEntity *target = entitylist->GetClientEntityFromHandle(entity->GetObserverTarget());
		if (pEntity != target)
			continue;

		IEngineClient::player_info_t entityInformation;
		engine->GetPlayerInfo(i, &entityInformation);

		if (strcmp(entityInformation.guid, "BOT") == 0)
			continue;

		list.push_back(entityInformation.name);
	}

	return list;
}