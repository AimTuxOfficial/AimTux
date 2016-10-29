#pragma once

#include "SDK/SDK.h"
#include "interfaces.h"
#include "settings.h"

namespace SkinChanger {
	extern bool ForceFullUpdate;

	void FrameStageNotify(ClientFrameStage_t stage);
	void FireEventClientSide(IGameEvent* event);
};