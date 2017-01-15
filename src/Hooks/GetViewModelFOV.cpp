#include "hooks.h"

float Hooks::GetViewModelFOV(void* thisptr)
{
	float fov = clientMode_vmt->GetOriginalMethod<GetViewModelFOVFn>(36)(thisptr);

	FOVChanger::GetViewModelFOV(fov);

	return fov;
}