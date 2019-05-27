#include "hitmarkers.h"

#include "../Utils/xorstring.h"
#include "../Utils/entity.h"
#include "../settings.h"
#include "../fonts.h"
#include "../settings.h"
#include "../interfaces.h"
#include "../Utils/draw.h"
#include "../Hooks/hooks.h"

bool Settings::ESP::Hitmarker::enabled = false;
bool Settings::ESP::Hitmarker::enemies = false;
bool Settings::ESP::Hitmarker::allies = false;
ColorVar Settings::ESP::Hitmarker::color = ImColor(255, 0, 0, 255);
int Settings::ESP::Hitmarker::duration = 2000;
int Settings::ESP::Hitmarker::size = 16;
int Settings::ESP::Hitmarker::innerGap = 5;
bool Settings::ESP::Hitmarker::Damage::enabled = false;
bool Settings::ESP::Hitmarker::Sounds::enabled = false;
Sound Settings::ESP::Hitmarker::Sounds::sound = Sound::NONE;

// int - damage dealt, long - timestamp
std::vector<std::pair<int, long>> damages;
long lastHitmarkerTimestamp = 0;

void Hitmarkers::Paint( ) {
	if ( !Settings::ESP::enabled || !Settings::ESP::Hitmarker::enabled )
		return;

	if ( !engine->IsInGame() )
		return;

	C_BasePlayer* localplayer = ( C_BasePlayer* ) entityList->GetClientEntity( engine->GetLocalPlayer() );
	if ( !localplayer )
		return;

	if ( !localplayer->GetAlive() )
		return;

	int duration = Settings::ESP::Hitmarker::duration;
	long now = Util::GetEpochTime();

	long diff = lastHitmarkerTimestamp + duration - now;
	if ( diff <= 0 )
		return;

	ImColor color =Settings::ESP::Hitmarker::color.Color();
	float sc = 1.0f/255.0f;
	color.Value.w = std::min( color.Value.w, (( diff * (color.Value.w / sc ) / duration * 2 ) ) * sc);

	int sides[4][2] = {
			{ -1, -1 },
			{ 1,  1 },
			{ -1, 1 },
			{ 1,  -1 }
	};
	for ( auto& it : sides )
		Draw::AddLine( Paint::engineWidth / 2 + ( Settings::ESP::Hitmarker::innerGap * it[0] ),
					   Paint::engineHeight / 2 + ( Settings::ESP::Hitmarker::innerGap * it[1] ),
					   Paint::engineWidth / 2 + ( Settings::ESP::Hitmarker::size * it[0] ),
					   Paint::engineHeight / 2 + ( Settings::ESP::Hitmarker::size * it[1] ), color );

	if ( !Settings::ESP::Hitmarker::Damage::enabled )
		return;

	int textHeight = (int)Draw::GetTextSize( XORSTR( "[cool]" ), esp_font ).y;

	for ( unsigned int i = 0; i < damages.size(); i++ ) {
		long timestamp = damages[i].second;
		long hitDiff = timestamp + duration - now;

		if ( hitDiff <= 0 ) {
			damages.erase( damages.begin() + i );
			continue;
		}

		int damage = damages[i].first;
		std::string damageStr = '-' + std::to_string( damage );

		color.Value.w = Settings::ESP::Hitmarker::color.Color().Value.w;
		color.Value.w = std::min( color.Value.w, (( hitDiff * ( color.Value.w / sc ) / duration * 2 ) *sc ));

		Draw::AddText( Paint::engineWidth / 2 + Settings::ESP::Hitmarker::size + 4,
					   Paint::engineHeight / 2 - Settings::ESP::Hitmarker::size - textHeight * i + 4, damageStr.c_str(), color);

	}
}

void Hitmarkers::FireGameEvent(IGameEvent* event)
{
	if (!Settings::ESP::Hitmarker::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (strcmp(event->GetName(), XORSTR("player_hurt")) != 0)
		return;

	int hurt_player_id = event->GetInt(XORSTR("userid"));
	int attacker_id = event->GetInt(XORSTR("attacker"));

	if (engine->GetPlayerForUserID(hurt_player_id) == engine->GetLocalPlayer())
		return;

	// TODO: show hitmarks while spectating?
	if (engine->GetPlayerForUserID(attacker_id) != engine->GetLocalPlayer())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BasePlayer* hurt_player = (C_BasePlayer*) entityList->GetClientEntity(engine->GetPlayerForUserID(hurt_player_id));
	if (!hurt_player)
		return;

	if (Entity::IsTeamMate(hurt_player, localplayer) && !Settings::ESP::Hitmarker::allies)
		return;

	if (!Entity::IsTeamMate(hurt_player, localplayer) && !Settings::ESP::Hitmarker::enemies)
		return;

	long now = Util::GetEpochTime();
	lastHitmarkerTimestamp = now;
	damages.insert(damages.begin(), std::pair<int, long>(event->GetInt(XORSTR("dmg_health")), now));

	if( Settings::ESP::Hitmarker::Sounds::enabled ){
		switch( Settings::ESP::Hitmarker::Sounds::sound ){
			case Sound::SPONGEBOB:
				engine->ClientCmd_Unrestricted( "play training\\scoreregular" );
				break;
			case Sound::HALFLIFE:
				engine->ClientCmd_Unrestricted( "play ui\\beep22" );
				break;
			case Sound::HALFLIFE2:
				engine->ClientCmd_Unrestricted( "play common\\beep" );
				break;
			case Sound::HALFLIFE3:
				engine->ClientCmd_Unrestricted( "play items\\medshot4" );
				break;
			case Sound::HALFLIFE4:
				engine->ClientCmd_Unrestricted( "play buttons\\blip1" );
				break;
			case Sound::BBGUNBELL:
				engine->ClientCmd_Unrestricted( "play training\\bell_impact" );
				break;
			case Sound::DOPAMINE:
				engine->ClientCmd_Unrestricted( "play ui\\csgo_ui_crate_open" );
				break;
			case Sound::WUB:
				engine->ClientCmd_Unrestricted( "play ui\\csgo_ui_store_rollover" );
				break;
			case Sound::PEDOYES:
				engine->ClientCmd_Unrestricted( "play radio\\legacy_yesss" );
				break;
			case Sound::MEME:
				engine->ClientCmd_Unrestricted( "play commander\\train_guntestcomplete_01" );
				break;
			case Sound::ERROR:
				engine->ClientCmd_Unrestricted( "play error" );
				break;
			case Sound::ORCHESTRAL:
				engine->ClientCmd_Unrestricted( "playvol player\\orch_hit_csharp_short 0.8" );
				break;
			default:
				break;
		}
	}
}
