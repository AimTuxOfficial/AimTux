#include "chantagchanger.h"

char* Settings::ClanTagChanger::value = (char *) "";

void ClanTagChanger::CreateMove(CUserCmd* cmd)
{
	if (!engine->IsInGame())
		return;

	if (strlen(Settings::ClanTagChanger::value) == 0)
		return;

	SendClanTag(Settings::ClanTagChanger::value, "");
}