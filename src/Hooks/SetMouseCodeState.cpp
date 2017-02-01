#include "hooks.h"

void Hooks::SetMouseCodeState(void* thisptr, ButtonCode_t code, MouseCodeState_t state)
{
	if (SetKeyCodeState::shouldListen && state == MouseCodeState_t::BUTTON_PRESSED)
	{
		SetKeyCodeState::shouldListen = false;
		*SetKeyCodeState::keyOutput = code;
		UI::UpdateWeaponSettings();
	}

	inputInternal_vmt->GetOriginalMethod<SetMouseCodeStateFn>(93)(thisptr, code, state);
}
