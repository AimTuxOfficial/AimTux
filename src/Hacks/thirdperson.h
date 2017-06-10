#pragma once

#include "../interfaces.h"
#include "../settings.h"

namespace ThirdPerson
{
	//Hooks
	void BeginFrame();
	void FrameStageNotify(ClientFrameStage_t stage);
}
