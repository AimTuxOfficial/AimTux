#include "hooks.h"

int Hooks::PumpWindowsMessageLoop(void* thisptr, void* unknown)
{
	if (UI::isVisible && !SetKeyCodeState::shouldListen)
		return 0;

	return launchermgrVMT->GetOriginalMethod<PumpWindowsMessageLoopFn>(19)(thisptr, unknown);
}
