#pragma once

#include "../SDK/IGameEvent.h"

namespace Hitmarkers
{
	//Hooks
	void FireGameEvent(IGameEvent* event);
	void Paint();
}
