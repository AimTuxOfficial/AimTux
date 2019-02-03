#include "hooks.h"

#include "../interfaces.h"
#include "../settings.h"

#include "../Hacks/chams.h"
#include "../Hacks/esp.h"

typedef void (*DrawModelExecuteFn) (void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);

void Hooks::DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	if (!Settings::ScreenshotCleaner::enabled || !engine->IsTakingScreenshot())
	{
		Chams::DrawModelExecute(thisptr, context, state, pInfo, pCustomBoneToWorld);
	}

	modelRenderVMT->GetOriginalMethod<DrawModelExecuteFn>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
	modelRender->ForcedMaterialOverride(nullptr);

	if (!Settings::ScreenshotCleaner::enabled || !engine->IsTakingScreenshot())
	{
		ESP::DrawModelExecute();
	}
}
