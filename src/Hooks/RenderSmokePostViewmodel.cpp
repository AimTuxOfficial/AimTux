#include "hooks.h"

#include "../interfaces.h"

void Hooks::RenderSmokePostViewmodel(void* thisptr)
{
	if (!NoSmoke::RenderSmokePostViewmodel())
		viewRenderVMT->GetOriginalMethod<RenderSmokePostViewmodelFn>(41)(thisptr);
}