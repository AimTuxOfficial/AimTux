#include "sdrsettings.h"

#include "../settings.h"
#include "../interfaces.h"

void SDRSettings::CreateMove(CUserCmd* cmd)
{
    *g_nagleTime = Settings::SDRSettings::nagleTime;
}