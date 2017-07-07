#include "autoaccept.h"

bool Settings::AutoAccept::enabled = false;

struct CServerConfirmedReservationCheckCallback
{
	char pad[0x2200];
};

void AutoAccept::PlaySound(const char* filename)
{
	if (!Settings::AutoAccept::enabled)
		return;

	if (engine->IsInGame())
		return;

	if (strcmp(filename, XORSTR("UI/competitive_accept_beep.wav")) != 0) // new wav file on autoaccept, thanks @flawww
		return;

	//CServerConfirmedReservationCheckCallback empty_callback;
	//IsReadyCallback(&empty_callback);
}
