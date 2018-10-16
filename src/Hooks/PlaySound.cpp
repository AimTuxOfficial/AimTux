#include "hooks.h"

void Hooks::PlaySound(void* thisptr, const char* filename)
{
	surfaceVMT->GetOriginalMethod<PlaySoundFn>(82)(thisptr, filename);
}