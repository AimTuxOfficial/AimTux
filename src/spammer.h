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
	extern std::vector<const char*> collections;
	extern std::vector<IEngineClient::player_info_t> killedPlayerQueue;

	void BeginFrame(float frameTime);
	void FireEventClientSide(IGameEvent* event);
}