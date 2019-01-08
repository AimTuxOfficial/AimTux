#pragma once

#include "../SDK/IGameEvent.h"

namespace ValveDSCheck
{
	extern bool forceUT;

	//Hooks
	void FireGameEvent(IGameEvent* event);
}
