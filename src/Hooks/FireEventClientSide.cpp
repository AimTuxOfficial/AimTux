#include "hooks.h"

bool Hooks::FireEventClientSide(void* thisptr, IGameEvent* event)
{
	SkinChanger::FireEventClientSide(event);

	return gameEvents_vmt->GetOriginalMethod<FireEventClientSideFn>(10)(thisptr, event);
}
