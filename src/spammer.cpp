#include "spammer.h"

/*---- Settings ----*/
bool Settings::Spammer::NormalSpammer::enabled = false;
bool Settings::Spammer::KillSpammer::enabled = false;
/*---- Settings ----*/

/*---- Externs ----*/
long timeStamp = 0;

std::vector<Spammer::SpamCollection> Spammer::collections =
{
	Spammer::SpamCollection("AimTux",
		{
			"AimTux owns me and all",
			"Your Windows p2c sucks my AimTux dry",
			"It's free as in FREEDOM!",
			"Tux only let me out so I could play this game, please be nice!",
			"Tux nutted but you keep sucken",
			">tfw no vac on Linux"
		}, 0)
};

Spammer::SpamCollection* Spammer::currentSpamCollection = &collections[0]; // Default 0
/*---- Externs ----*/

void Spammer::Tick()
{
	if (!Settings::Spammer::NormalSpammer::enabled)
	{
		return;
	}
	
	// Give the random number generator a new seed based of the current time
	std::srand(std::time(NULL));

	// Grab the current time in milliseconds
	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	
	if (currentTime_ms - timeStamp > (1000 + currentSpamCollection->delay))
	{
		// Grab a random message string
		std::string message = currentSpamCollection->messages[std::rand() % currentSpamCollection->messages.size()];

		// Construct a command with our message
		pstring str;
		str << "say ";
		str << message;

		// Execute our constructed command
		engine->ExecuteClientCmd(str.c_str());

		// Update the time stamp
		timeStamp = currentTime_ms;
	}
}


bool Spammer::FireEventClientSide (IGameEvent* event)
{
	if (!Settings::Spammer::KillSpammer::enabled)
	{
		return false;
	}
	
	if (!std::strcmp(event->GetName(), "player_death"))
	{
		int attacker_id = event->GetInt ("attacker");
		int deadPlayer_id = event->GetInt ("userid");
		
		
		// Make sure both IDs are valid
		if (attacker_id && deadPlayer_id)
		{
			// Make sure it's not a suicide.
			if (attacker_id == deadPlayer_id)
			{
				return false;
			}
			
			// Get the attackers information
			IEngineClient::player_info_t attacker_info;
			engine->GetPlayerInfo(attacker_id, &attacker_info);
			
			// Get the dead players information
			IEngineClient::player_info_t deadPlayer_info;
			engine->GetPlayerInfo (deadPlayer_id, &deadPlayer_info);
			
			
			
			// Make sure we're the one who killed someone...
			if (engine->GetPlayerForUserID (attacker_id) != engine->GetLocalPlayer())
			{
				return false;
			}
			
			// Grab the current time in milliseconds
			long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
					std::chrono::system_clock::now().time_since_epoch()).count();
			
			if (currentTime_ms - timeStamp > 1000)
			{
				// Construct a command with our message
				pstring str;
				str << "say " << deadPlayer_info.name << " just got OWNED by AimTux!";
				
				engine->Print (str.c_str());
				
				// Execute our constructed command
				engine->ExecuteClientCmd(str.c_str());
				
				// Update the time stamp
				timeStamp = currentTime_ms;
			}
		}
	}
}

