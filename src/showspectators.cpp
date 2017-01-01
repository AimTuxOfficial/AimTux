#include "showspectators.h"

bool Settings::ShowSpectators::enabled = true;

std::list<int> ShowSpectators::GetObservervators(int playerId)
{
	std::list<int> list;

	if (!engine->IsInGame())
		return list;

	C_BasePlayer* player = (C_BasePlayer*) entitylist->GetClientEntity(playerId);
	if (!player)
		return list;

	if (!player->GetAlive())
	{
		C_BasePlayer* observerTarget = (C_BasePlayer*) entitylist->GetClientEntityFromHandle(player->GetObserverTarget());
		if (!observerTarget)
			return list;

		player = observerTarget;
	}

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BasePlayer *entity = (C_BasePlayer*) entitylist->GetClientEntity(i);
		if (!entity)
			continue;

		if (player->GetDormant() || player->GetAlive())
			continue;

		C_BasePlayer* target = (C_BasePlayer*) entitylist->GetClientEntityFromHandle(player->GetObserverTarget());
		if (player != target)
			continue;

		list.push_back(i);
	}

	return list;
}