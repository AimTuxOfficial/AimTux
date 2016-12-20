#include "hooks.h"

bool Hooks::FireEventClientSide(void* thisptr, IGameEvent* event)
{
	Aimbot::FireEventClientSide(event);
	Resolver::FireEventClientSide(event);
	SkinChanger::FireEventClientSide(event);
	Spammer::FireEventClientSide(event);

	if (event && strcmp(event->GetName(), "cs_game_disconnected") == 0)
		playerResource = nullptr;

	return gameEvents_vmt->GetOriginalMethod<FireEventClientSideFn>(10)(thisptr, event);
}