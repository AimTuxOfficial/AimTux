#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../Utils/xorstring.h"

namespace ValveDSCheck
{
	extern bool forceUT;

	void FireGameEvent(IGameEvent* event);
}
