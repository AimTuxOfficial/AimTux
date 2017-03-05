#pragma once

#include "../SDK/SDK.h"
#include "../Utils/draw.h"
#include "../Utils/entity.h"
#include "../Utils/pstring.h"
#include "../interfaces.h"
#include "../settings.h"

namespace Resolver
{
extern std::vector<int64_t> Players;

void FrameStageNotify(ClientFrameStage_t stage);
void PostFrameStageNotify(ClientFrameStage_t stage);
void FireGameEvent(IGameEvent* event);
}
