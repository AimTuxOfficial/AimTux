#include "spammer.h"
#include "skins.h"

bool Settings::Spammer::PositionSpammer::enabled = false;
bool Settings::Spammer::PositionSpammer::say_team = false;
bool Settings::Spammer::KillSpammer::enabled = false;
bool Settings::Spammer::KillSpammer::say_team = false;
char* Settings::Spammer::KillSpammer::message = strdup("$nick just got OWNED by AimTux!!");
bool Settings::Spammer::NormalSpammer::enabled = false;
bool Settings::Spammer::NormalSpammer::say_team = false;
std::vector<std::string> Settings::Spammer::NormalSpammer::messages = {
		"AimTux owns me and all",
		"Your Windows p2c sucks my AimTux dry",
		"It's free as in FREEDOM!",
		"Tux only let me out so I could play this game, please be nice!",
		"Tux nutted but you keep sucken",
		">tfw no vac on Linux"
};

std::vector<int> killedPlayerQueue;

void Spammer::BeginFrame(float frameTime)
{
	// Grab the current time in milliseconds
	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp < 850)
		return;

	// Kill spammer
	if (Settings::Spammer::KillSpammer::enabled && killedPlayerQueue.size() > 0)
	{
		IEngineClient::player_info_t playerInfo;
		engine->GetPlayerInfo(killedPlayerQueue[0], &playerInfo);

		// Prepare dead player's nickname without ';' & '"' characters
		// as they might cause user to execute a command.
		std::string dead_player_name = std::string(playerInfo.name);
		dead_player_name.erase(std::remove(dead_player_name.begin(), dead_player_name.end(), ';'), dead_player_name.end());
		dead_player_name.erase(std::remove(dead_player_name.begin(), dead_player_name.end(), '"'), dead_player_name.end());

		// Construct a command with our message
		pstring str;
		str << (Settings::Spammer::KillSpammer::say_team ? "say_team" : "say");
		str << " \"" << Util::ReplaceString(Settings::Spammer::KillSpammer::message, "$nick", dead_player_name) << "\"";

		// Execute our constructed command
		engine->ExecuteClientCmd(str.c_str());

		// Remove the first element from the vector
		killedPlayerQueue.erase(killedPlayerQueue.begin(), killedPlayerQueue.begin() + 1);
	}
	else if (Settings::Spammer::PositionSpammer::enabled)
	{
		C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
		static int lastId = 1;

		for (int i = lastId; i < engine->GetMaxClients(); i++)
		{
			C_BaseEntity *entity = entitylist->GetClientEntity(i);

			lastId++;
			if (lastId == engine->GetMaxClients())
				lastId = 1;

			if (!entity
				|| entity->GetDormant()
				|| !entity->GetAlive()
				|| entity->GetTeam() == localplayer->GetTeam())
				continue;

			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(i, &entityInformation);

			C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(entity->GetActiveWeapon());

			std::string modelName = Util::GetValueByKey(guns, *active_weapon->GetItemDefinitionIndex());
			if (modelName == "")
			{
				modelName = std::string(active_weapon->GetClientClass()->m_pNetworkName);
				if (strstr(modelName.c_str(), "Weapon"))
					modelName = modelName.substr(7, modelName.length() - 7);
				else
					modelName = modelName.substr(1, modelName.length() - 1);
			}

			// Prepare player's nickname without ';' & '"' characters
			// as they might cause user to execute a command.
			std::string player_name = std::string(entityInformation.name);
			player_name.erase(std::remove(player_name.begin(), player_name.end(), ';'), player_name.end());
			player_name.erase(std::remove(player_name.begin(), player_name.end(), '"'), player_name.end());

			// Remove end line character
			player_name.erase(std::remove(player_name.begin(), player_name.end(), '\n'), player_name.end());

			// Construct a command with our message
			pstring str;
			str << (Settings::Spammer::PositionSpammer::say_team ? "say_team" : "say") << " \""
			<< player_name << " | "
			<< modelName << " | "
			<< "$" << entity->GetMoney() << " | "
			<< ESP::Ranks[*(*csPlayerResource)->GetCompetitiveRanking(i)] << " | "
			<< *(*csPlayerResource)->GetCompetitiveWins(i) << " wins | "
			<< entity->GetHealth() << "HP | "
			<< entity->GetLastPlaceName() << "\"";

			// Execute our constructed command
			engine->ExecuteClientCmd(str.c_str());

			break;
		}
	}
	else if (Settings::Spammer::NormalSpammer::enabled)
	{
		// Give the random number generator a new seed based of the current time
		std::srand(std::time(NULL));

		// Grab a random message string
		std::string message = Settings::Spammer::NormalSpammer::messages[std::rand() % Settings::Spammer::NormalSpammer::messages.size()];

		// Construct a command with our message
		pstring str;
		str << (Settings::Spammer::NormalSpammer::say_team ? "say_team" : "say") << " ";
		str << message;

		// Execute our constructed command
		engine->ExecuteClientCmd(str.c_str());
	}

	// Update the time stamp
	timeStamp = currentTime_ms;
}


void Spammer::FireEventClientSide(IGameEvent* event)
{
	if (!Settings::Spammer::KillSpammer::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (strcmp(event->GetName(), "player_death") != 0)
		return;

	int attacker_id = engine->GetPlayerForUserID(event->GetInt("attacker"));
	int deadPlayer_id = engine->GetPlayerForUserID(event->GetInt("userid"));

	// Make sure it's not a suicide.x
	if (attacker_id == deadPlayer_id)
		return;

	// Make sure we're the one who killed someone...
	if (attacker_id != engine->GetLocalPlayer())
		return;

	killedPlayerQueue.push_back(deadPlayer_id);
}
