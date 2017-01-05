#include "hooks.h"

int Hooks::IN_KeyEvent(void* thisptr, int eventcode, int keynum, const char* currentbinding)
{
	return client_vmt->GetOriginalMethod<IN_KeyEventFn>(20)(thisptr, eventcode, keynum, currentbinding);
}