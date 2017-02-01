#include "hooks.h"

bool SetKeyCodeState::shouldListen = false;
ButtonCode_t* SetKeyCodeState::keyOutput = nullptr;

void Hooks::SetKeyCodeState(void* thisptr, ButtonCode_t code, bool bPressed)
{
	if (SetKeyCodeState::shouldListen && bPressed)
	{
		SetKeyCodeState::shouldListen = false;
		*SetKeyCodeState::keyOutput = code;
		UI::UpdateWeaponSettings();
	}

	inputInternal_vmt->GetOriginalMethod<SetKeyCodeStateFn>(92)(thisptr, code, bPressed);
}
