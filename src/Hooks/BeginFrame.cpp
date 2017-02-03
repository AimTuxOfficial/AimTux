#include "hooks.h"

void Hooks::BeginFrame(void* thisptr, float frameTime)
{
	ClanTagChanger::BeginFrame(frameTime);
	NameChanger::BeginFrame(frameTime);
	NameStealer::BeginFrame(frameTime);
	Spammer::BeginFrame(frameTime);
	Radar::BeginFrame();
	SniperCrosshair::BeginFrame();

	if (!engine->IsInGame())
	{
		CreateMove::SendPacket = true;
		*bSendPacket = CreateMove::SendPacket;
	}

	Skins::Localize();

	return materialVMT->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
}
