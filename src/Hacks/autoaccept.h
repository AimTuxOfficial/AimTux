#pragma once

#include "../interfaces.h"
#include "../settings.h"

namespace AutoAccept
{
	//Hooks
	void PlaySound(const char* filename);
}

extern IsReadyCallbackFn IsReadyCallback;
