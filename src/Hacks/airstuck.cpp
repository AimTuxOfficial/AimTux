#include "airstuck.h"

#include "../settings.h"
#include "../interfaces.h"

void Airstuck::CreateMove(CUserCmd* cmd)
{
	if (!Settings::Airstuck::enabled)
		return;

	if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
		return;

	if (inputSystem->IsButtonDown(Settings::Airstuck::key))
		cmd->tick_count = 16777216;
}
