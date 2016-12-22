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

		dlight_t* dLight = effects->CL_AllocDlight(i);

		if (entity->GetTeam() == localPlayer->GetTeam())
		{
			dLight->color.r = (unsigned char)(Settings::Dlights::ally_color.Value.x / 255);
			dLight->color.g = (unsigned char)(Settings::Dlights::ally_color.Value.y / 255);
			dLight->color.b = (unsigned char)(Settings::Dlights::ally_color.Value.z / 255);
		}
		else
		{
			dLight->color.r = (unsigned char)(Settings::Dlights::enemy_color.Value.x / 255);
			dLight->color.g = (unsigned char)(Settings::Dlights::enemy_color.Value.y / 255);
			dLight->color.b = (unsigned char)(Settings::Dlights::enemy_color.Value.z / 255);
		}

		dLight->radius = Settings::Dlights::radius;
		dLight->key = i;
		dLight->m_Direction = entity->GetVecOrigin();
		dLight->origin = entity->GetVecOrigin();
		dLight->die = globalvars->curtime + 1.f;
		dLight->decay = 20;
	}
}
