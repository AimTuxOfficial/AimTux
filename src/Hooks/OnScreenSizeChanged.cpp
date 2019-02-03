#include "hooks.h"

#include "../fonts.h"
#include "../interfaces.h"

typedef void (*OnScreenSizeChangedFn) (void*, int, int);

void Hooks::OnScreenSizeChanged(void* thisptr, int oldwidth, int oldheight)
{
	surfaceVMT->GetOriginalMethod<OnScreenSizeChangedFn>(116)(thisptr, oldwidth, oldheight);

	Fonts::SetupFonts();
}