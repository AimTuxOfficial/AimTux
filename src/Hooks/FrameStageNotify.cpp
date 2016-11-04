#include "hooks.h"

void Hooks::FrameStageNotify(void* thisptr, ClientFrameStage_t stage)
{
	SkinChanger::FrameStageNotify(stage);
	Noflash::FrameStageNotify(stage);
	
	View::FrameStageNotify (stage);
	
	client_vmt->GetOriginalMethod<FrameStageNotifyFn>(36)(thisptr, stage);
	
	View::PostFrameStageNotify (stage);
}