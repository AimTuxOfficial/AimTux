#include "hooks.h"

void Hooks::RenderView(void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw)
{
	FOVChanger::RenderView(setup, hudViewSetup, nClearFlags, whatToDraw);

	viewRender_vmt->GetOriginalMethod<RenderViewFn>(6)(thisptr, setup, hudViewSetup, nClearFlags, whatToDraw);
}