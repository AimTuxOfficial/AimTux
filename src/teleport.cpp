#include "teleport.h"

bool Settings::Teleport::enabled = false;
ButtonCode_t Settings::Teleport::key = ButtonCode_t::KEY_RALT;

void Teleport::CreateMove(CUserCmd *cmd)
{
#ifdef UNTRUSTED_SETTINGS
	if (!Settings::Teleport::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (!input->IsButtonDown(Settings::Teleport::key))
		return;

	cmd->viewangles = QAngle(0, 1e+37, 0);
#endif
}
