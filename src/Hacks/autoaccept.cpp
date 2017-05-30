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

	if (strcmp(filename, "UI/competitive_accept_beep.wav") != 0)
		return;

	CServerConfirmedReservationCheckCallback empty_callback;
	IsReadyCallback(&empty_callback);
}
