#include "hitmarkers.h"

bool Settings::ESP::Hitmarker::enabled = false;
bool Settings::ESP::Hitmarker::enemies = false;
bool Settings::ESP::Hitmarker::allies = false;
ImColor Settings::ESP::Hitmarker::color = ImColor(180, 50, 50, 255);
int Settings::ESP::Hitmarker::duration = 2000;
int Settings::ESP::Hitmarker::size = 16;
int Settings::ESP::Hitmarker::inner_gap = 5;

long lastHitmarkerTimestamp = 0;

void Hitmarkers::Paint()
{
	if (!Settings::ESP::enabled || !Settings::ESP::Hitmarker::enabled)
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
		return;

	int duration = Settings::ESP::Hitmarker::duration;

	long diff = lastHitmarkerTimestamp + duration - Util::GetEpochTime();
	if (diff <= 0)
		return;

	int width, height;
	engine->GetScreenSize(width, height);

	Color color = Color::FromImColor(Settings::ESP::Hitmarker::color);
	color.a = std::min(color.a, (int)(diff * color.a / duration * 2));

	int sides[4][2] = { {-1, -1}, {1, 1}, {-1, 1}, {1, -1} };
	for (auto& it : sides)
		Draw::Line(width / 2 + (Settings::ESP::Hitmarker::inner_gap * it[0]), height / 2 + (Settings::ESP::Hitmarker::inner_gap * it[1]), width / 2 + (Settings::ESP::Hitmarker::size * it[0]), height / 2 + (Settings::ESP::Hitmarker::size * it[1]), color);

	// TODO: draw given damage string next to the hitmarker?
}

void Hitmarkers::FireEventClientSide(IGameEvent* event)
{
	if (!event)
		return;

	if (strcmp(event->GetName(), "player_hurt") != 0)
		return;

	int hurt_player_id = event->GetInt("userid");
	int attacker_id = event->GetInt("attacker");

	if (engine->GetPlayerForUserID(hurt_player_id) == engine->GetLocalPlayer())
		return;

	// TODO: show hitmarks while spectating?
	if (engine->GetPlayerForUserID(attacker_id) != engine->GetLocalPlayer())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BasePlayer* hurt_player = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetPlayerForUserID(hurt_player_id));
	if (!hurt_player)
		return;

	if (hurt_player->GetTeam() == localplayer->GetTeam() && !Settings::ESP::Hitmarker::allies)
		return;

	if (hurt_player->GetTeam() != localplayer->GetTeam() && !Settings::ESP::Hitmarker::enemies)
		return;

	lastHitmarkerTimestamp = Util::GetEpochTime();
}