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
		C_BasePlayer* player = (C_BasePlayer*) entitylist->GetClientEntity(i);
		if (!player)
			continue;

		if (player->GetDormant() || !player->GetAlive())
			continue;

		*player->GetSpotted() = true;
	}
}