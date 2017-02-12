#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"

namespace View
{
	void FrameStageNotify(ClientFrameStage_t stage);
	void PostFrameStageNotify(ClientFrameStage_t stage);
}
