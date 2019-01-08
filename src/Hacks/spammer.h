#pragma once

#include "../SDK/IGameEvent.h"

namespace Spammer
{
	//Hooks
	void BeginFrame(float frameTime);
	void FireGameEvent(IGameEvent* event);
}
