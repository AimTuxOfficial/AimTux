#include "spammer.h"

/*---- Settings ----*/
bool Settings::Spammer::enabled = false;
/*---- Settings ----*/

/*---- Externs ----*/
long timeStamp = 0;

std::vector<Spammer::SpamCollection> Spammer::collections =
{
	Spammer::SpamCollection ("AimTux",
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

void Spammer::Tick ()
{
	if (!Settings::Spammer::enabled)
		return;

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