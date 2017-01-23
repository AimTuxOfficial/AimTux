#include "hooks.h"

bool Hooks::FireEvent(void* thisptr, IGameEvent* event, bool bDontBroadcast)
{
	Hitmarkers::FireEvent(event, bDontBroadcast);

	return gameEvents_vmt->GetOriginalMethod<FireEventFn>(9)(thisptr, event, bDontBroadcast);
}
