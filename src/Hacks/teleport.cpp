#include "teleport.h"

bool Settings::Teleport::enabled = false;
ButtonCode_t Settings::Teleport::key = ButtonCode_t::KEY_RALT;

void Teleport::CreateMove(CUserCmd *cmd)
{
	return;
	if (!ValveDSCheck::forceUT && (*csGameRules) && (*csGameRules)->IsValveDS())
		Settings::Teleport::enabled = false;

	if (!Settings::Teleport::enabled)
		return;

	if (!inputSystem->IsButtonDown(Settings::Teleport::key))
		return;

	cmd->viewangles.y = 1e+37;
}
