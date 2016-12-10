#include "hooks.h"

void Hooks::SetKeyCodeState(void* thisptr, ButtonCode_t code, bool bPressed)
{
	inputInternal_vmt->GetOriginalMethod<SetKeyCodeStateFn>(92)(thisptr, code, bPressed);
}