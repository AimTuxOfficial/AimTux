#include "hooks.h"

#include "../interfaces.h"
#include "../Hacks/nosmoke.h"

typedef void (*RenderSmokePostViewmodelFn) (void*);

void Hooks::RenderSmokePostViewmodel(void* thisptr)
{
	if (!NoSmoke::RenderSmokePostViewmodel())
		viewRenderVMT->GetOriginalMethod<RenderSmokePostViewmodelFn>(42)(thisptr);
}