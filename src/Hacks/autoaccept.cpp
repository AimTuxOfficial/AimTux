#include "autoaccept.h"

#include "../Utils/xorstring.h"
#include "../settings.h"

bool Settings::AutoAccept::enabled = false;

void AutoAccept::EmitSound(const char* pSoundEntry)
{
	if (!Settings::AutoAccept::enabled)
		return;

	if (strcmp(pSoundEntry, XORSTR("UIPanorama.popup_accept_match_beep")) == 0 && SetLocalPlayerReady)
	{
		SetLocalPlayerReady("");
	}
}
