#include "hooks.h"

float RenderView::currentFOV = 90.0f;

void Hooks::RenderView(void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw)
{
	FOVChanger::RenderView(setup, hudViewSetup, nClearFlags, whatToDraw);

	RenderView::currentFOV = setup.fov;

	viewRender_vmt->GetOriginalMethod<RenderViewFn>(6)(thisptr, setup, hudViewSetup, nClearFlags, whatToDraw);
}