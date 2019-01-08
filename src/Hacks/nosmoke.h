#pragma once

#include "../SDK/definitions.h"

namespace NoSmoke
{
	void Cleanup();

	//Hooks
	bool RenderSmokePostViewmodel();
	void FrameStageNotify(ClientFrameStage_t stage);
};
