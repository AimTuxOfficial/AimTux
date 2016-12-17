#include "hooks.h"

void Hooks::BeginFrame(void* thisptr, float frameTime)
{
	ESP::BeginFrame(frameTime);
	Radar::BeginFrame(frameTime);

	return material_vmt->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
}