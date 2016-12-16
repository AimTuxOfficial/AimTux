#include "hooks.h"

bool SDLInput::Enabled = true;

int Hooks::HandleSDLInput(void* thisptr, wchar_t* unknown)
{
	if (!SDLInput::Enabled)
	{
		return 0;
	}

	return sdlmanager_vmt->GetOriginalMethod<HandleSDLInputFn>(19)(thisptr, unknown);
}
