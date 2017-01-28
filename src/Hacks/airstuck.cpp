#include "airstuck.h"

bool Settings::Airstuck::enabled = false;
ButtonCode_t Settings::Airstuck::key = ButtonCode_t::KEY_F;

void Airstuck::CreateMove(CUserCmd* cmd)
{
	if (!Settings::Airstuck::enabled)
		return;

	if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
		return;

	if (inputSystem->IsButtonDown(Settings::Airstuck::key))
		cmd->tick_count = 16777216;
}
