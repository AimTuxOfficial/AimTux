#pragma once

#include "../interfaces.h"
#include "../settings.h"

namespace NoSmoke
{
	void Cleanup();

	//Hooks
	bool RenderSmokePostViewmodel();
	void FrameStageNotify(ClientFrameStage_t stage);
};
