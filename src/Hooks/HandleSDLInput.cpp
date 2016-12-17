#include "hooks.h"

int Hooks::HandleSDLInput(void* thisptr, wchar_t* unknown)
{
	if (UI::isVisible && !SetKeyCodeState::shouldListen)
		return 0;

	return sdlmanager_vmt->GetOriginalMethod<HandleSDLInputFn>(19)(thisptr, unknown);
}
