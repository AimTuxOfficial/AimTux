#include "hooks.h"

bool Hooks::FireEventClientSide(void* thisptr, IGameEvent* event)
{
	Aimbot::FireEventClientSide(event);
	Resolver::FireEventClientSide(event);
	SkinChanger::FireEventClientSide(event);
	Spammer::FireEventClientSide(event);

	if (event && strcmp(event->GetName(), "player_connect_full") == 0)
		if (event->GetInt("userid") && engine->GetPlayerForUserID(event->GetInt("userid")) == engine->GetLocalPlayer())
			Hooker::HookPlayerResource();

	return gameEvents_vmt->GetOriginalMethod<FireEventClientSideFn>(10)(thisptr, event);
}