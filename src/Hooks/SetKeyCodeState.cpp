#include "hooks.h"

void Hooks::SetKeyCodeState(void* thisptr, ButtonCode_t code, bool bPressed)
{
	if (code == ButtonCode_t::KEY_INSERT && bPressed)
		UIVisible = !UIVisible;

	inputInternal_vmt->GetOriginalMethod<SetKeyCodeStateFn>(92)(thisptr, code, bPressed);
}