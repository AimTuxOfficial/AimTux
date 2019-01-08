#pragma once

#include "../SDK/IGameEvent.h"

namespace NameStealer
{
	extern int entityId;

	//Hooks
	void BeginFrame(float frameTime);
	void FireGameEvent(IGameEvent* event);
};
