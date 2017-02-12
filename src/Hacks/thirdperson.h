#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"

namespace ThirdPerson
{
	void BeginFrame();
	void FrameStageNotify(ClientFrameStage_t stage);
}
