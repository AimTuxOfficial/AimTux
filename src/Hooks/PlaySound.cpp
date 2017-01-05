#include "hooks.h"

void Hooks::PlaySound(void* thisptr, const char* filename)
{
	AutoAccept::PlaySound(filename);

	surface_vmt->GetOriginalMethod<PlaySoundFn>(82)(thisptr, filename);
}