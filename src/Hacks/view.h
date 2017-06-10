#pragma once

#include "../interfaces.h"
#include "../settings.h"

namespace View
{
	//Hooks
	void FrameStageNotify(ClientFrameStage_t stage);
	void PostFrameStageNotify(ClientFrameStage_t stage);
}
