#include "hooks.h"

#include "../interfaces.h"

void Hooks::EmitSound2(void* thisptr, IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, int nSeed, soundlevel_t iSoundLevel, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, StartSoundParams_t& params)
{
	ESP::EmitSound(iEntIndex, pSample);
	AutoAccept::EmitSound(pSoundEntry);
	soundVMT->GetOriginalMethod<EmitSound2Fn>(6)(thisptr, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, nSeed, iSoundLevel, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, params);
}