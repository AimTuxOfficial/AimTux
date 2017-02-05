#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"

namespace ValveDSCheck
{
	extern bool forceUT;

	void FireGameEvent(IGameEvent* event);
}
