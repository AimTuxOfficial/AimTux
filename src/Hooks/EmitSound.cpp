#include "hooks.h"

void Hooks::EmitSound(void* thisptr, IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity)
{
	printf("%d - %s\n", iEntIndex, pSample);

	sound_vmt->GetOriginalMethod<EmitSoundFn>(5)(thisptr, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, flAttenuation, nSeed, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);
}