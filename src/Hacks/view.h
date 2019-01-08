#pragma once

#include "../SDK/definitions.h"

namespace View
{
	//Hooks
	void FrameStageNotify(ClientFrameStage_t stage);
	void PostFrameStageNotify(ClientFrameStage_t stage);
}
