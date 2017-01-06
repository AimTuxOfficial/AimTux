#include "hooks.h"

void Hooks::RenderSmokePreViewmodel(void* thisptr, bool draw_viewmodel)
{
	if (!NoSmoke::RenderSmokePreViewmodel())
		viewRender_vmt->GetOriginalMethod<RenderSmokePreViewmodelFn>(41)(thisptr, draw_viewmodel);
}