#include "hooks.h"

#include "../interfaces.h"
#include "../ATGUI/atgui.h"

int Hooks::PumpWindowsMessageLoop(void* thisptr, void* unknown)
{
	if (UI::isVisible && !SetKeyCodeState::shouldListen)
		return 0;

	return launcherMgrVMT->GetOriginalMethod<PumpWindowsMessageLoopFn>(19)(thisptr, unknown);
}
