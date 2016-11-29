#include "radar.h"

bool Settings::Radar::enabled = false;

void Radar::PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (!Settings::Radar::enabled)
		return;

	if (!engine->IsInGame())
		return;

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BaseEntity *entity = entitylist->GetClientEntity(i);
		if (!entity)
			continue;

		if (entity->GetDormant() || !entity->GetAlive())
			continue;

		*entity->GetSpotted() = true;
	}
}