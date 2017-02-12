#include "hooks.h"

void Hooks::FrameStageNotify(void* thisptr, ClientFrameStage_t stage)
{
	CustomGlow::FrameStageNotify(stage);
	SkinChanger::FrameStageNotifyModels(stage);
	SkinChanger::FrameStageNotifySkins(stage);
	Noflash::FrameStageNotify(stage);
	View::FrameStageNotify(stage);
	Resolver::FrameStageNotify(stage);
	NoSky::FrameStageNotify(stage);
	ASUSWalls::FrameStageNotify(stage);
	NoSmoke::FrameStageNotify(stage);
	ThirdPerson::FrameStageNotify(stage);

	if (SkinChanger::forceFullUpdate)
	{
		GetLocalClient(-1)->m_nDeltaTick = -1;
		SkinChanger::forceFullUpdate = false;
	}

	clientVMT->GetOriginalMethod<FrameStageNotifyFn>(36)(thisptr, stage);

	Resolver::PostFrameStageNotify(stage);
	View::PostFrameStageNotify(stage);
}
