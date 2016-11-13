#include "airstuck.h"

void Airstuck::CreateMove(CUserCmd* cmd)
{
	if (!cSettings.Airstuck.enabled)
		return;

	if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
		return;

	if (input->IsButtonDown(cSettings.Airstuck.key))
		cmd->tick_count = 16777216;
}
