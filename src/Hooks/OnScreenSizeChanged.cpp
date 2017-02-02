#include "hooks.h"

void Hooks::OnScreenSizeChanged(void* thisptr, int oldwidth, int oldheight)
{
	surfaceVMT->GetOriginalMethod<OnScreenSizeChangedFn>(116)(thisptr, oldwidth, oldheight);

	Fonts::SetupFonts();
}