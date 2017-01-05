#pragma once

#include "../SDK/SDK.h"
#include "../draw.h"
#include "../interfaces.h"
#include "../entity.h"

namespace Hitmarkers
{
	void Paint();
	void FireEventClientSide(IGameEvent* event);
}