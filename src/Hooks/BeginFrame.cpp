#include "hooks.h"

void Hooks::BeginFrame(void* thisptr, float frameTime)
{
	ClanTagChanger::BeginFrame(frameTime);
	NameChanger::BeginFrame(frameTime);
	NameStealer::BeginFrame(frameTime);
	Spammer::BeginFrame(frameTime);
	Radar::BeginFrame();
	SniperCrosshair::BeginFrame();
	ThirdPerson::BeginFrame();
	DisablePostProcessing::BeginFrame();

	if (!engine->IsInGame())
	{
		CreateMove::sendPacket = true;
		*bSendPacket = CreateMove::sendPacket;
	}

	Skins::Localize();

	return materialVMT->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
}
