#ifndef __SPAMMER_H_
#define __SPAMMER_H_

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "interfaces.h"
#include "settings.h"
#include "pstring.h"

namespace Spammer
{
	struct SpamCollection
	{
		std::string name;					// Name of the spam collection, will be useful for GUI
		std::vector<std::string> messages;	// List of messages to be spammed into the chat
		unsigned int delay;					// Delay AFTER the required 1000 ms sleep

		SpamCollection(std::string name, std::vector<std::string> messages, unsigned int delay)
		{
			this->name = name;
			this->messages = messages;
			this->delay = delay;
		}
	};

	extern std::vector<SpamCollection> collections;
	extern SpamCollection* currentSpamCollection;

	void CreateMove(CUserCmd* cmd);
	void FireEventClientSide(IGameEvent* event);
}

#endif