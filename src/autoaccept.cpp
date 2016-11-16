#include "autoaccept.h"

bool Settings::AutoAccept::enabled = true;

struct CServerConfirmedReservationCheckCallback {
	char pad[0x2200];
};

void AutoAccept::PlaySound(const char* filename)
{
	if (!Settings::AutoAccept::enabled)
		return;

	if (strcmp(filename, "weapons/hegrenade/beep.wav") != 0)
		return;

	if (engine->IsInGame())
		return;

	CServerConfirmedReservationCheckCallback empty_callback;
	IsReadyCallback(&empty_callback);
}