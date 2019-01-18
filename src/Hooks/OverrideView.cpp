#include "hooks.h"

#include "../interfaces.h"
#include "../settings.h"

#include "../Hacks/fovchanger.h"
#include "../Hacks/thirdperson.h"

float OverrideView::currentFOV = 90.0f;

void Hooks::OverrideView(void* thisptr, CViewSetup* pSetup)
{
	if (!Settings::ScreenshotCleaner::enabled || !engine->IsTakingScreenshot())
	{
		FOVChanger::OverrideView(pSetup);
		ThirdPerson::OverrideView(pSetup);
	}

	OverrideView::currentFOV = pSetup->fov;

	clientModeVMT->GetOriginalMethod<OverrideViewFn>(19)(thisptr, pSetup);
}
