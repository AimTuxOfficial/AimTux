#include "noflash.h"

bool Settings::Noflash::enabled = false;
float Settings::Noflash::value = 160.0f;

void Noflash::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!engine->IsInGame())
		return;

	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (Settings::Noflash::enabled && Settings::ESP::enabled)
		*localplayer->GetFlashMaxAlpha() = 255.0f - Settings::Noflash::value;
	else
		*localplayer->GetFlashMaxAlpha() = 255.0f;
}
