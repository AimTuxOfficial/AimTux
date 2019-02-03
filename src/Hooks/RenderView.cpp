#include "hooks.h"

#include "../interfaces.h"

typedef void (*RenderViewFn) (void*, CViewSetup&, CViewSetup&, unsigned int, int);

void Hooks::RenderView(void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw)
{
	viewRenderVMT->GetOriginalMethod<RenderViewFn>(6)(thisptr, setup, hudViewSetup, nClearFlags, whatToDraw);
}