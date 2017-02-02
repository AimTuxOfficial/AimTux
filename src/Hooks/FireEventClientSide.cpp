#include "hooks.h"

bool Hooks::FireEventClientSide(void* thisptr, IGameEvent* event)
{
	SkinChanger::FireEventClientSide(event);

	return gameEventsVMT->GetOriginalMethod<FireEventClientSideFn>(10)(thisptr, event);
}
