#include "hooks.h"

void Hooks::EmitSound(void* thisptr, IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, float flAttenuation, int nSeed, soundlevel_t iSoundlevel, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity)
{
	if (strstr(pSample, "footstep") != NULL)
		printf("%d - %s\n", iEntIndex, pSample);

	ESP::EmitSound(iEntIndex, pSample);

	sound_vmt->GetOriginalMethod<EmitSoundFn>(6)(thisptr, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, flAttenuation, nSeed, iSoundlevel, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);
}