#include "fov.h"

bool Settings::FOV::enabled = false;
int Settings::FOV::value = 120;

void FOV::FrameStageNotify(ClientFrameStage_t stage)
{
	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localPlayer)
		return;

	if (Settings::FOV::enabled)
		*localPlayer->GetFOV() = Settings::FOV::value;
	else
		*localPlayer->GetFOV() = 0;
}