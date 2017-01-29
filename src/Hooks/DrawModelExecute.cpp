#include "hooks.h"

void Hooks::DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	modelRender_vmt->ReleaseVMT();

	if (!Settings::ScreenshotCleaner::enabled || !engine->IsTakingScreenshot())
	{
		Chams::DrawModelExecute(thisptr, context, state, pInfo, pCustomBoneToWorld);
	}

	modelRender->DrawModelExecute(context, state, pInfo, pCustomBoneToWorld);
	modelRender->ForcedMaterialOverride(NULL);

	if (!Settings::ScreenshotCleaner::enabled || !engine->IsTakingScreenshot())
	{
		ESP::DrawModelExecute(thisptr, context, state, pInfo, pCustomBoneToWorld);
	}

	modelRender_vmt->ApplyVMT();
}
