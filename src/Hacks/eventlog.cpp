#include "eventlog.h"
#include <string>

#include "../Utils/xorstring.h"
#include "../Utils/entity.h"
#include "../settings.h"
#include "../fonts.h"
#include "../interfaces.h"
#include "../Utils/draw.h"
#include "../Hooks/hooks.h"

std::vector<std::pair<std::string, long>> logToShow;
long lastLogTimestamp = 0;
bool Settings::Eventlog::showEnemies = false;
bool Settings::Eventlog::showTeammates = false;
float Settings::Eventlog::duration = 5000;

void Eventlog::Paint( ) {
	if ( !Settings::Eventlog::showEnemies && !Settings::Eventlog::showTeammates )
		return;

	if ( !engine->IsInGame() )
		return;

	C_BasePlayer* localplayer = ( C_BasePlayer* ) entityList->GetClientEntity( engine->GetLocalPlayer() );
	if ( !localplayer )
		return;

	if ( !localplayer->GetAlive() )
		return;

	int duration = Settings::Eventlog::duration;
	long now = Util::GetEpochTime();

	long diff = lastLogTimestamp + duration - now;
	if ( diff <= 0 )
		return;

	ImColor color = Settings::GrenadePrediction::color.Color();
	float sc = 1.0f/255.0f;
	color.Value.w = std::min( color.Value.w, (( diff * (color.Value.w / sc ) / duration * 2 ) ) * sc);


	int textHeight = (int)Draw::GetTextSize( XORSTR( "[cool]" ), esp_font ).y;

	for ( unsigned int i = 0; i < logToShow.size(); i++ ) {
		long timestamp = logToShow[i].second;
		long hitDiff = timestamp + duration - now;

		if ( hitDiff <= 0 ) {
			logToShow.erase( logToShow.begin() + i );
			continue;
		}

		std::string showLog = logToShow[i].first;

		color.Value.w = Settings::GrenadePrediction::color.Color().Value.w;
		color.Value.w = std::min( color.Value.w, (( hitDiff * ( color.Value.w / sc ) / duration * 2 ) *sc ));

		Draw::AddText( 20,
					   40 - textHeight * i, showLog.c_str(), color);

	}	
}

void Eventlog::FireGameEvent(IGameEvent* event)
{
	if (!Settings::Eventlog::showEnemies && !Settings::Eventlog::showTeammates)
		return;

	if (!engine->IsInGame())
		return;

	if (strstr(event->GetName(), XORSTR("player_hurt"))){

		int hurt_player_id = event->GetInt(XORSTR("userid"));
		int attacker_id = event->GetInt(XORSTR("attacker"));

		if (engine->GetPlayerForUserID(hurt_player_id) == engine->GetLocalPlayer())
			return;

		if (engine->GetPlayerForUserID(attacker_id) != engine->GetLocalPlayer())
			return;

		C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer)
			return;

		C_BasePlayer* hurt_player = (C_BasePlayer*) entityList->GetClientEntity(engine->GetPlayerForUserID(hurt_player_id));
		if (!hurt_player)
			return;

		if (Entity::IsTeamMate(hurt_player, localplayer) && !Settings::Eventlog::showTeammates)
			return;

		if (!Entity::IsTeamMate(hurt_player, localplayer) && !Settings::Eventlog::showEnemies)
			return;


		IEngineClient::player_info_t damageToPlayer;		
		engine->GetPlayerInfo(engine->GetPlayerForUserID(hurt_player_id), &damageToPlayer);

		long now = Util::GetEpochTime();
		lastLogTimestamp = now;

		std::string damageLog = "damage: -";
		damageLog += std::to_string(event->GetInt(XORSTR("dmg_health")));
		damageLog += XORSTR(" to ");
		damageLog += std::string(damageToPlayer.name);
		if ((hurt_player->GetHealth()) - (event->GetInt(XORSTR("dmg_health"))) <= 0){
			damageLog += XORSTR(" (dead)");
		} else if ((hurt_player->GetHealth()) - (event->GetInt(XORSTR("dmg_health"))) > 0){
			damageLog += XORSTR(" (left ");
			damageLog += std::to_string((hurt_player->GetHealth()) - (event->GetInt(XORSTR("dmg_health"))));
			damageLog += XORSTR(" hp)");
		}

		logToShow.insert(logToShow.begin(), std::pair<std::string, long>(damageLog, now));

	} else if (strstr(event->GetName(), XORSTR("item_purchase"))){

		int buyer_player_id = event->GetInt(XORSTR("userid"));

		if (engine->GetPlayerForUserID(buyer_player_id) == engine->GetLocalPlayer())
			return;

		C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer)
			return;

		C_BasePlayer* buyer_player = (C_BasePlayer*) entityList->GetClientEntity(engine->GetPlayerForUserID(buyer_player_id));
		if (!buyer_player)
			return;

		if (Entity::IsTeamMate(buyer_player, localplayer) && !Settings::Eventlog::showTeammates)
			return;

		if (!Entity::IsTeamMate(buyer_player, localplayer) && !Settings::Eventlog::showEnemies)
			return;


		IEngineClient::player_info_t buyerInformation;		
		engine->GetPlayerInfo(engine->GetPlayerForUserID(buyer_player_id), &buyerInformation);

		long now = Util::GetEpochTime();
		lastLogTimestamp = now;

		std::string boughtLog = std::string(buyerInformation.name);
		boughtLog += XORSTR(" bought ");

		std::string deletefromname = "weapon_";
		std::string weaponname = event->GetString(XORSTR("weapon"));
		std::string::size_type whereisstring = weaponname.find(deletefromname);
		weaponname.erase(whereisstring, deletefromname.length());
		boughtLog += weaponname;		

		logToShow.insert(logToShow.begin(), std::pair<std::string, long>(boughtLog, now));

	} else if (strstr(event->GetName(), XORSTR("enter_bombzone"))){

		int bomb_player_id = event->GetInt(XORSTR("userid"));

		if (engine->GetPlayerForUserID(bomb_player_id) == engine->GetLocalPlayer())
			return;

		C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer)
			return;

		C_BasePlayer* bomb_player = (C_BasePlayer*) entityList->GetClientEntity(engine->GetPlayerForUserID(bomb_player_id));
		if (!bomb_player)
			return;

		if (Entity::IsTeamMate(bomb_player, localplayer) && !Settings::Eventlog::showTeammates)
			return;

		if (!Entity::IsTeamMate(bomb_player, localplayer) && !Settings::Eventlog::showEnemies)
			return;


		if (!event->GetBool("hasbomb"))
			return;

		IEngineClient::player_info_t bomberInformation;		
		engine->GetPlayerInfo(engine->GetPlayerForUserID(bomb_player_id), &bomberInformation);

		long now = Util::GetEpochTime();
		lastLogTimestamp = now;

		std::string bombLog = std::string(bomberInformation.name);
		bombLog += " enter bomb-site with bomb";

		logToShow.insert(logToShow.begin(), std::pair<std::string, long>(bombLog, now));

	} else if (strstr(event->GetName(), XORSTR("bomb_begindefuse"))){

		int defuse_player_id = event->GetInt(XORSTR("userid"));

		if (engine->GetPlayerForUserID(defuse_player_id) == engine->GetLocalPlayer())
			return;

		C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer)
			return;

		C_BasePlayer* defuse_player = (C_BasePlayer*) entityList->GetClientEntity(engine->GetPlayerForUserID(defuse_player_id));
		if (!defuse_player)
			return;

		if (Entity::IsTeamMate(defuse_player, localplayer) && !Settings::Eventlog::showTeammates)
			return;

		if (!Entity::IsTeamMate(defuse_player, localplayer) && !Settings::Eventlog::showEnemies)
			return;


		IEngineClient::player_info_t defuserInformation;		
		engine->GetPlayerInfo(engine->GetPlayerForUserID(defuse_player_id), &defuserInformation);

		long now = Util::GetEpochTime();
		lastLogTimestamp = now;

		std::string defuseLog = std::string(defuserInformation.name);
		defuseLog += " defuse bomb ";

		if (event->GetBool("haskit")){
			defuseLog += "with defuse-kit";
		} else if (!event->GetBool("haskit")){
			defuseLog += "without defuse-kit";
		}

		logToShow.insert(logToShow.begin(), std::pair<std::string, long>(defuseLog, now));

	} else if (strstr(event->GetName(), XORSTR("bomb_beginplant"))){ 
		//To add: check on which bomb-site is player planting 

		int plant_player_id = event->GetInt(XORSTR("userid"));

		if (engine->GetPlayerForUserID(plant_player_id) == engine->GetLocalPlayer())
			return;

		C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer)
			return;

		C_BasePlayer* planter_player = (C_BasePlayer*) entityList->GetClientEntity(engine->GetPlayerForUserID(plant_player_id));
		if (!planter_player)
			return;

		if (Entity::IsTeamMate(planter_player, localplayer) && !Settings::Eventlog::showTeammates)
			return;

		if (!Entity::IsTeamMate(planter_player, localplayer) && !Settings::Eventlog::showEnemies)
			return;


		IEngineClient::player_info_t planterInformation;		
		engine->GetPlayerInfo(engine->GetPlayerForUserID(plant_player_id), &planterInformation);

		long now = Util::GetEpochTime();
		lastLogTimestamp = now;

		std::string plantLog = std::string(planterInformation.name);
		plantLog += " started planting bomb";
		//plantLog += std::to_string(event->GetInt("site"));

		logToShow.insert(logToShow.begin(), std::pair<std::string, long>(plantLog, now));

	}
}
