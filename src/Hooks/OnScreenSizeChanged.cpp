#include "hooks.h"

void Hooks::OnScreenSizeChanged(void* thisptr, int oldwidth, int oldheight)
{
	surface_vmt->GetOriginalMethod<OnScreenSizeChangedFn>(116)(thisptr, oldwidth, oldheight);

	Fonts::SetupFonts();
}