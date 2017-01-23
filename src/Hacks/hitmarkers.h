#pragma once

#include "../SDK/SDK.h"
#include "../Utils/draw.h"
#include "../interfaces.h"
#include "../Utils/entity.h"

namespace Hitmarkers
{
	void Paint();
	void FireEvent(IGameEvent* event, bool bDontBroadcast);
}
