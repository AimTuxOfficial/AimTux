#include "noflash.h"
void Noflash::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!engine->IsInGame())
		return;

	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (cSettings.Noflash.enabled)
		*localplayer->GetFlashMaxAlpha() = 255.0f - cSettings.Noflash.value;
	else
		*localplayer->GetFlashMaxAlpha() = 255.0f;
}