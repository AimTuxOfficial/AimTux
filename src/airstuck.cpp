#include "airstuck.h"

bool Settings::Airstuck::enabled = false;

void Airstuck::CreateMove(CUserCmd* cmd)
{
	if (!Settings::Airstuck::enabled)
		return;

	if (cmd->buttons & IN_ATTACK)
		return;

	if (input->IsButtonDown(ButtonCode_t::KEY_F))
		cmd->tick_count = 16777216;
}
