#include "hooks.h"

float OverrideView::currentFOV = 90.0f;

void Hooks::OverrideView(void* thisptr, CViewSetup* pSetup)
{
	FOVChanger::OverrideView(pSetup);

	OverrideView::currentFOV = pSetup->fov;

	clientMode_vmt->GetOriginalMethod<OverrideViewFn>(18)(thisptr, pSetup);
}