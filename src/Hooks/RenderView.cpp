#include "hooks.h"

float RenderView::currentFOV = 90.0f;

void Hooks::RenderView(void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw)
{
	FOVChanger::RenderView(setup, hudViewSetup, nClearFlags, whatToDraw);

	RenderView::currentFOV = setup.fov;

	viewRender_vmt->GetOriginalMethod<RenderViewFn>(6)(thisptr, setup, hudViewSetup, nClearFlags, whatToDraw);
}

void Hooks::RenderSmokePreViewmodel(void* thisptr, bool draw_viewmodel)
{
	NoSmoke::RenderSmokePreViewmodel(draw_viewmodel);

	viewRender_vmt->GetOriginalMethod<RenderSmokePreViewmodelFn>(40)(thisptr, draw_viewmodel);
}