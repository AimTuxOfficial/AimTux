#pragma once

#include <vector>
#include "../interfaces.h"
#include "../settings.h"
#include "../Utils/pstring.h"
#include "../Utils/util.h"

namespace Spammer
{
	//Hooks
	void BeginFrame(float frameTime);
	void FireGameEvent(IGameEvent* event);
}
