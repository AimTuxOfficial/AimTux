#include "hooks.h"

#include "../ATGUI/atgui.h"
#include "../interfaces.h"

typedef void (*SetMouseCodeStateFn) (void*, ButtonCode_t, MouseCodeState_t);

void Hooks::SetMouseCodeState(void* thisptr, ButtonCode_t code, MouseCodeState_t state)
{
	if (SetKeyCodeState::shouldListen && state == MouseCodeState_t::BUTTON_PRESSED)
	{
		SetKeyCodeState::shouldListen = false;
		*SetKeyCodeState::keyOutput = code;
		UI::UpdateWeaponSettings();
	}

	inputInternalVMT->GetOriginalMethod<SetMouseCodeStateFn>(93)(thisptr, code, state);
}
