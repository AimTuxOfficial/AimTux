#pragma once
#include <vector>

#include "SDK/IGameEvent.h"

class EventListener : public IGameEventListener2
{
public:
	EventListener(std::vector<const char*> events);
	~EventListener();

	void FireGameEvent(IGameEvent* event);
	int GetEventDebugID() override;
};
