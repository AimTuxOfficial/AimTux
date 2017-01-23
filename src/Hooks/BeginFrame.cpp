#include "hooks.h"

void Hooks::BeginFrame(void* thisptr, float frameTime)
{
	ESP::BeginFrame(frameTime);
	ClanTagChanger::BeginFrame(frameTime);
	NameChanger::BeginFrame(frameTime);
	NameStealer::BeginFrame(frameTime);
	Spammer::BeginFrame(frameTime);
	Radar::BeginFrame();

	if (!engine->IsInGame())
	{
		CreateMove::SendPacket = true;
		*bSendPacket = CreateMove::SendPacket;
	}

	Skins::Localize();

	return material_vmt->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
}