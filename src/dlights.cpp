#include "dlights.h"

bool Settings::Dlights::enabled = false;
float Settings::Dlights::radius = 500.0f;
ImColor Settings::Dlights::ally_color = ImColor(0, 50, 200, 255);
ImColor Settings::Dlights::enemy_color = ImColor(200, 0, 50, 255);

void Dlights::Paint()
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

		Color color;
		if (entity->GetTeam() == localPlayer->GetTeam())
			color = Color::FromImColor(Settings::Dlights::ally_color);
		else
			color = Color::FromImColor(Settings::Dlights::enemy_color);

		dlight_t* dLight = effects->CL_AllocDlight(i);
		dLight->key = i;
		dLight->color.r = (unsigned char) color.r;
		dLight->color.g = (unsigned char) color.g;
		dLight->color.b = (unsigned char) color.b;
		dLight->color.exponent = true;
		dLight->flags = DLIGHT_NO_MODEL_ILLUMINATION;
		dLight->m_Direction = entity->GetVecOrigin();
		dLight->origin = entity->GetVecOrigin();
		dLight->radius = Settings::Dlights::radius;
		dLight->die = globalvars->curtime + 0.1f;
		dLight->decay = 20.0f;
	}
}
