#include "valvedscheck.h"

bool ValveDSCheck::forceUT = false;

void ValveDSCheck::FireEventClientSide(IGameEvent* event)
{
	if (!event)
		return;

	if (strcmp(event->GetName(), "player_connect_full") == 0 || strcmp(event->GetName(), "cs_game_disconnected") == 0)
	{
		if (event->GetInt("userid") && engine->GetPlayerForUserID(event->GetInt("userid")) != engine->GetLocalPlayer())
			return;

		ValveDSCheck::forceUT = false;
	}
}