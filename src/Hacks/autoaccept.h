#pragma once

#include "../SDK/SDK.h"
#include "../interfaces.h"
#include "../settings.h"

namespace AutoAccept
{
	void PlaySound(const char* filename);
}

extern IsReadyCallbackFn IsReadyCallback;
