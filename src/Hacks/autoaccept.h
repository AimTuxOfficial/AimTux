#pragma once

#include "../interfaces.h"
#include "../settings.h"

namespace AutoAccept
{
	//Hooks
	void EmitSound(const char* pSoundEntry);
}

extern SetLocalPlayerReadyFn SetLocalPlayerReady;
