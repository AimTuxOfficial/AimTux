#include "hooks.h"

float Hooks::GetViewModelFOV(void* thisptr)
{
	float fov = clientMode_vmt->GetOriginalMethod<GetViewModelFOVFn>(36)(thisptr);

	if (!Settings::ScreenshotCleaner::enabled || !engine->IsTakingScreenshot())
		FOVChanger::GetViewModelFOV(fov);

	return fov;
}