#include "teleport.h"

void Teleport::CreateMove(CUserCmd *cmd)
{
#ifdef UNTRUSTED_SETTINGS
	if (!cSettings.Teleport.enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (cvar->FindVar("cl_mouseenable")->GetInt() == 0)
		return;

	if (!input->IsButtonDown(cSettings.Teleport.key))
		return;

	cmd->viewangles.y = 1e+37;
#endif
}