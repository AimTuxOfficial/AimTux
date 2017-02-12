#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "../interfaces.h"
#include "../settings.h"
#include "../Utils/pstring.h"
#include "../Utils/util.h"

namespace Spammer
{
	void BeginFrame(float frameTime);
	void FireGameEvent(IGameEvent* event);
}
