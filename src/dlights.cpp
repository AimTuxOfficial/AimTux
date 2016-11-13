#include "dlights.h"

void Dlights::PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (!cSettings.ESP.enabled)
		return;

	if (!cSettings.Dlights.enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());

	if (!localPlayer)
		return;

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BaseEntity *entity = entitylist->GetClientEntity(i);
		if (!entity)
			continue;

		dlight_t* dLight = effects->CL_AllocDlight(i);

		if (entity->GetTeam() == localPlayer->GetTeam())
		{
			dLight->color.r = cSettings.Dlights.ally_color.r;
			dLight->color.g = cSettings.Dlights.ally_color.g;
			dLight->color.b = cSettings.Dlights.ally_color.b;
		}
		else
		{
			dLight->color.r = cSettings.Dlights.enemy_color.r;
			dLight->color.g = cSettings.Dlights.enemy_color.g;
			dLight->color.b = cSettings.Dlights.enemy_color.b;
		}

		dLight->radius = cSettings.Dlights.radius;
		dLight->key = i;
		dLight->m_Direction = entity->GetVecOrigin();
		dLight->origin = entity->GetVecOrigin();
		dLight->die = globalvars->curtime + 1.f;
		dLight->decay = 20;
	}
}
