#pragma once

#include <vector>
#include <cstdint>
#include "../SDK/definitions.h"
#include "../SDK/IGameEvent.h"

namespace Resolver
{
	extern std::vector<int64_t> Players;

	//Hooks
	void FrameStageNotify(ClientFrameStage_t stage);
	void PostFrameStageNotify(ClientFrameStage_t stage);
	void FireGameEvent(IGameEvent* event);
}
