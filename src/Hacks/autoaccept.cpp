#include "autoaccept.h"

#include "../Utils/xorstring.h"
#include "../settings.h"

void AutoAccept::EmitSound(const char* pSoundEntry)
{
	if (!Settings::AutoAccept::enabled)
		return;

	if (strcmp(pSoundEntry, XORSTR("UIPanorama.popup_accept_match_beep")) == 0 && SetLocalPlayerReady)
	{
		SetLocalPlayerReady("");
	}
}
