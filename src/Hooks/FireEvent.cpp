#include "hooks.h"

#include "../interfaces.h"

bool Hooks::FireEvent(void* thisptr, IGameEvent* event, bool bDontBroadcast)
{
	return gameEventsVMT->GetOriginalMethod<FireEventFn>(9)(thisptr, event, bDontBroadcast);
}
