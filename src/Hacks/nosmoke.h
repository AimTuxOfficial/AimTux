#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"

namespace NoSmoke
{
	void RenderSmokePreViewmodel(bool& draw_viewmodel);
	void FrameStageNotify(ClientFrameStage_t stage);
};