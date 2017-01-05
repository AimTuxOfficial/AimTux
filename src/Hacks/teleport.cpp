#include "teleport.h"

bool Settings::Teleport::enabled = false;
ButtonCode_t Settings::Teleport::key = ButtonCode_t::KEY_RALT;

void Teleport::CreateMove(CUserCmd *cmd)
{
	if (!Settings::Teleport::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (!(*csGameRules) || (*csGameRules)->IsValveDS())
		return;

	if (!input->IsButtonDown(Settings::Teleport::key))
		return;

	cmd->viewangles.y = 1e+37;
}