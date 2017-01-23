#include "namestealer.h"

bool Settings::NameStealer::enabled = false;
int Settings::NameStealer::team = 1;

void NameStealer::BeginFrame(float frameTime)
{
	if (!Settings::NameStealer::enabled)
		return;

	if (!engine->IsInGame())
		return;

	long currentTime_ms = Util::GetEpochTime();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp < 350)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	static int entityId = -1;

	do
	{
		entityId++;

		if (entityId >= engine->GetMaxClients())
			entityId = 0;

		if (entityId == 0)
		{
			NameChanger::SetName("\n\xAD\xAD\xAD");

			timeStamp = currentTime_ms;

			return;
		}

		if ((*csPlayerResource) && (*csPlayerResource)->GetConnected(entityId))
		{
			if (Settings::NameStealer::team == 0 && (*csPlayerResource)->GetTeam(entityId) != localplayer->GetTeam())
				return;

			if (Settings::NameStealer::team == 1 && (*csPlayerResource)->GetTeam(entityId) == localplayer->GetTeam())
				return;

			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(entityId, &entityInformation);

			NameChanger::SetName(Util::PadStringRight(entityInformation.name, strlen(entityInformation.name) + 1));

			timeStamp = currentTime_ms;

			return;
		}
	} while (entityId < engine->GetMaxClients());
}