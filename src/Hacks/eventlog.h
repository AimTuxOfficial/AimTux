#pragma once

#include "../SDK/IGameEvent.h"

namespace Eventlog
{
	//Hooks
	void FireGameEvent(IGameEvent* event);
	void Paint();
}
