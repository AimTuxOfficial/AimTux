#include "hooks.h"

#include "../interfaces.h"

#include "../Hacks/skinchanger.h"

typedef bool (*FireEventClientSideFn) (void*, IGameEvent*);

bool Hooks::FireEventClientSide(void* thisptr, IGameEvent* event)
{
	SkinChanger::FireEventClientSide(event);

	return gameEventsVMT->GetOriginalMethod<FireEventClientSideFn>(10)(thisptr, event);
}
