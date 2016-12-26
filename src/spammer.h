#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "interfaces.h"
#include "settings.h"
#include "pstring.h"
#include "util.h"

namespace Spammer
{
	void BeginFrame(float frameTime);
	void FireEventClientSide(IGameEvent* event);
}