#include "hooks.h"

void Hooks::FrameStageNotify(void* thisptr, ClientFrameStage_t stage)
{
	CustomGlow::FrameStageNotify(stage);
	SkinChanger::FrameStageNotifyWeapons(stage);
	SkinChanger::FrameStageNotifyGloves(stage);
	Noflash::FrameStageNotify(stage);
	View::FrameStageNotify(stage);
	Resolver::FrameStageNotify(stage);
	NoSky::FrameStageNotify(stage);
	ASUSWalls::FrameStageNotify(stage);
	NoSmoke::FrameStageNotify(stage);

	if (SkinChanger::forceFullUpdate)
	{
		GetClientState(-1)->m_nDeltaTick = -1;
		SkinChanger::forceFullUpdate = false;
	}

	client_vmt->GetOriginalMethod<FrameStageNotifyFn>(36)(thisptr, stage);

	Resolver::PostFrameStageNotify(stage);
	View::PostFrameStageNotify(stage);
}