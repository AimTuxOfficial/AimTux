#include "hooks.h"

void Hooks::RenderSmokePostViewmodel(void* thisptr)
{
	if (!NoSmoke::RenderSmokePostViewmodel())
		viewRender_vmt->GetOriginalMethod<RenderSmokePostViewmodelFn>(41)(thisptr);
}