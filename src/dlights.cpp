#include "dlights.h"

bool Settings::Dlights::enabled = false;
float Settings::Dlights::radius = 500.0f;
Color Settings::Dlights::ally_color = Color(0, 50, 200);
Color Settings::Dlights::enemy_color = Color(200, 0, 50);

void Dlights::PaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (!Settings::ESP::enabled)
		return;

	if (!Settings::Dlights::enabled)
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
			dLight->color.r = Settings::Dlights::ally_color.r;
			dLight->color.g = Settings::Dlights::ally_color.g;
			dLight->color.b = Settings::Dlights::ally_color.b;
		}
		else
		{
			dLight->color.r = Settings::Dlights::enemy_color.r;
			dLight->color.g = Settings::Dlights::enemy_color.g;
			dLight->color.b = Settings::Dlights::enemy_color.b;
		}

		dLight->radius = Settings::Dlights::radius;
		dLight->key = i;
		dLight->m_Direction = entity->GetVecOrigin();
		dLight->origin = entity->GetVecOrigin();
		dLight->die = globalvars->curtime + 1.f;
		dLight->decay = 20;
	}
}
