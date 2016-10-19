#pragma once

#include "SDK/SDK.h"
#include "interfaces.h"
#include "settings.h"

namespace SkinChanger {
	void FrameStageNotify(ClientFrameStage_t stage);
	void FireEventClientSide(IGameEvent* event);
};