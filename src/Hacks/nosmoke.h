#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"

namespace NoSmoke
{
	bool RenderSmokePostViewmodel();
	void FrameStageNotify(ClientFrameStage_t stage);
	void Cleanup();
};
