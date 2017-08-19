#pragma once

#include "../Utils/draw.h"
#include "../interfaces.h"
#include "../Utils/entity.h"

namespace Hitmarkers
{
	//Hooks
	void FireGameEvent(IGameEvent* event);
	void Paint();
}
