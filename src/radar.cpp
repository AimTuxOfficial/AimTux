#include "radar.h"

bool Settings::Radar::enabled = false;

void Radar::BeginFrame(float frameTime)
{
	if (!Settings::Radar::enabled)
		return;

	if (!engine->IsInGame())
		return;

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BaseEntity *entity = entitylist->GetClientEntity(i);
		if (!entity)
			continue;

		if (entity->GetDormant() || !entity->GetAlive())
			continue;

		*entity->GetSpotted() = true;
	}
}