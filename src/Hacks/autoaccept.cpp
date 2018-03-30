#include "autoaccept.h"

bool Settings::AutoAccept::enabled = false;

/* This doesn't matter too much, it just has to be big enough for the game to write various parts of it */
struct CServerConfirmedReservationCheckCallback {
	char pad[0x12788];
};

void AutoAccept::PlaySound(const char* filename)
{
	if (!Settings::AutoAccept::enabled)
		return;

	if (engine->IsInGame())
		return;

	if (strcmp(filename, XORSTR("!UI/competitive_accept_beep.wav")) != 0)
		return;

	CServerConfirmedReservationCheckCallback empty_callback;
	IsReadyCallback(&empty_callback);
}
