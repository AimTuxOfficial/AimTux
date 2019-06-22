#pragma once

#include "../SDK/CViewRender.h"
#include "../Hooks/hooks.h"

namespace ThirdPerson
{
	//Hooks
	void OverrideView(CViewSetup* pSetup);
	void FrameStageNotify(ClientFrameStage_t stage);
}
