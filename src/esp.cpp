#include "esp.h"

bool Settings::ESP::enabled = true;

bool WorldToScreen (const Vector &vOrigin, Vector &vScreen)
{
	return ( debugOverlay->ScreenPosition( vOrigin, vScreen ));
}

Vector2D WorldToScreen (const Vector &vOrigin)
{
	Vector vec;
	debugOverlay->ScreenPosition( vOrigin, vec );
	return LOC(vec.x, vec.y);
}

static wchar_t* cwConvert(const char* text)
{
	const size_t size = strlen(text) + 1;
	wchar_t* wText = new wchar_t[size];
	mbstowcs(wText, text, size);
	return wText;
}

void DrawESPBox (Vector vecOrigin, Vector vecViewOffset, Color color, int width, int additionalHeight)
{
	//SIDES

	Vector2D a = WorldToScreen (vecOrigin + Vector(width, width, additionalHeight));
	Vector2D b = WorldToScreen (vecOrigin + vecViewOffset + Vector (width, width, additionalHeight));

	Draw::DrawLine (a, b, color);


	a = WorldToScreen (vecOrigin + Vector(-width, width, additionalHeight));
	b = WorldToScreen (vecOrigin + vecViewOffset + Vector (-width, width, additionalHeight));

	Draw::DrawLine (a, b, color);


	a = WorldToScreen (vecOrigin + Vector(-width, -width, additionalHeight));
	b = WorldToScreen (vecOrigin + vecViewOffset + Vector (-width, -width, additionalHeight));

	Draw::DrawLine (a, b, color);

	a = WorldToScreen (vecOrigin + Vector(width, -width, additionalHeight));
	b = WorldToScreen (vecOrigin + vecViewOffset + Vector (width, -width, additionalHeight));

	Draw::DrawLine (a, b, color);


	//TOP

	a = WorldToScreen (vecOrigin + vecViewOffset + Vector(width, width, additionalHeight));
	b = WorldToScreen (vecOrigin + vecViewOffset + Vector (width, -width, additionalHeight));

	Draw::DrawLine (a, b, color);


	a = WorldToScreen (vecOrigin + vecViewOffset + Vector(width, width, additionalHeight));
	b = WorldToScreen (vecOrigin + vecViewOffset + Vector (-width, width, additionalHeight));

	Draw::DrawLine (a, b, color);

	a = WorldToScreen (vecOrigin + vecViewOffset + Vector(-width, -width, additionalHeight));
	b = WorldToScreen (vecOrigin + vecViewOffset + Vector (-width, width, additionalHeight));

	Draw::DrawLine (a, b, color);


	a = WorldToScreen (vecOrigin + vecViewOffset + Vector(width, -width, additionalHeight));
	b = WorldToScreen (vecOrigin + vecViewOffset + Vector (-width, -width, additionalHeight));

	Draw::DrawLine (a, b, color);


	//BOTTOM

	a = WorldToScreen (vecOrigin + Vector(width, width, additionalHeight));
	b = WorldToScreen (vecOrigin + Vector (width, -width, additionalHeight));

	Draw::DrawLine (a, b, color);


	a = WorldToScreen (vecOrigin + Vector(width, width, additionalHeight));
	b = WorldToScreen (vecOrigin + Vector (-width, width, additionalHeight));

	Draw::DrawLine (a, b, color);

	a = WorldToScreen (vecOrigin + Vector(-width, -width, additionalHeight));
	b = WorldToScreen (vecOrigin + Vector (-width, width, additionalHeight));

	Draw::DrawLine (a, b, color);


	a = WorldToScreen (vecOrigin + Vector(width, -width, additionalHeight));
	b = WorldToScreen (vecOrigin + Vector (-width, -width, additionalHeight));

	Draw::DrawLine (a, b, color);
}

void ESP::Tick ()
{
	CBaseEntity* pLocal = entitylist->GetClientEntity(engine->GetLocalPlayer());
	if(pLocal)
	for(int i = 0; i < 64; ++i)
	{
		CBaseEntity* entity = entitylist->GetClientEntity(i);
		C_BasePlayer* player = reinterpret_cast<C_BasePlayer*>(entity);

		if (!entity || entity == pLocal ||
				player->GetDormant() || player->GetLifeState() != LIFE_ALIVE || player->GetHealth() <= 0)
			continue;

		Color color;

		C_BasePlayer* localPlayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

		int playerTeam = localPlayer->m_iTeamNum;
		int entityTeam = entity->m_iTeamNum;

		if (playerTeam != entityTeam)
		{
			color.r = 200;
			color.b = 50;
		}
		else
		{
			color.b = 200;
			color.g = 50;
		}

		CEngineClient::player_info_t pInfo;
		engine->GetPlayerInfo(i, &pInfo);
		
		ESP::DrawPlayerBox	(localPlayer, entity);
		ESP::DrawTracer		(localPlayer, entity);
		ESP::DrawPlayerName	(localPlayer, entity, i);
	}
}

void ESP::DrawTracer (C_BasePlayer* localPlayer, CBaseEntity* entity)
{
	Color color;
	
	int playerTeam = localPlayer->GetTeam();
	int entityTeam = reinterpret_cast<C_BasePlayer*>(entity)->GetTeam();
	
	if (playerTeam != entityTeam)
	{
		color.r = 200;
		color.b = 50;
	}
	else
	{
		color.b = 200;
		color.g = 50;
	}
	
	Vector s_vecLocalPlayer_s;
	Vector s_vecEntity_s;
	if (!WorldToScreen(localPlayer->m_vecOrigin, s_vecLocalPlayer_s) &&
		!WorldToScreen(entity->m_vecOrigin, s_vecEntity_s) &&
		localPlayer->GetHealth() > 0)
	{
		Draw::DrawLine (LOC(s_vecLocalPlayer_s.x, s_vecLocalPlayer_s.y), LOC(s_vecEntity_s.x, s_vecEntity_s.y), color);
	}
}

void ESP::DrawPlayerBox (C_BasePlayer* localPlayer, CBaseEntity* entity)
{
	Color color;

	int playerTeam = localPlayer->GetTeam();
	int entityTeam = reinterpret_cast<C_BasePlayer*>(entity)->GetTeam();
	
	if (playerTeam != entityTeam)
	{
		color.r = 200;
		color.b = 50;
	}
	else
	{
		color.b = 200;
		color.g = 50;
	}
	
	int width = 14;
	int additionalHeight = 6;
	
	Vector vecOrigin = entity->m_vecOrigin;
	Vector vecViewOffset = entity->m_vecViewOffset;
	
	Vector s_vecLocalPlayer_s;
	if (!WorldToScreen(vecOrigin, s_vecLocalPlayer_s))
		DrawESPBox (vecOrigin, vecViewOffset, color, width, additionalHeight);
}

void ESP::DrawPlayerName (C_BasePlayer* localPlayer, CBaseEntity* entity, int entityIndex)
{
	Color color;

	int playerTeam = localPlayer->GetTeam();
	int entityTeam = reinterpret_cast<C_BasePlayer*>(entity)->GetTeam();
	
	if (playerTeam != entityTeam)
	{
		color.r = 150;
		color.b = 10;
	}
	else
	{
		color.b = 200;
		color.g = 100;
	}
	
	CEngineClient::player_info_t entityInformation;
	engine->GetPlayerInfo(entityIndex, &entityInformation);
	
	Vector vecOrigin = entity->m_vecOrigin;
	
	Vector s_vecEntity_s;
	if (!WorldToScreen(vecOrigin, s_vecEntity_s))
		Draw::DrawString (CONV(entityInformation.name), LOC(s_vecEntity_s.x, s_vecEntity_s.y), color, 33, true);
}


