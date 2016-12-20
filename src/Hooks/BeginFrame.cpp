#include "hooks.h"

void Hooks::BeginFrame(void* thisptr, float frameTime)
{
	if (playerResource == nullptr)
		Hooker::HookPlayerResource();

	ESP::BeginFrame(frameTime);
	Radar::BeginFrame(frameTime);
	ClanTagChanger::BeginFrame(frameTime);
	NameChanger::BeginFrame(frameTime);
	Spammer::BeginFrame(frameTime);

	return material_vmt->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
}