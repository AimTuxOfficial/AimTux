#pragma once

#include "../interfaces.h"
#include "../Utils/xorstring.h"

namespace ValveDSCheck
{
	extern bool forceUT;

	//Hooks
	void FireGameEvent(IGameEvent* event);
}
