#pragma once

class EventListener : public IGameEventListener2
{
public:
	EventListener(std::vector<const char*> events)
	{
		for (auto& it : events)
		{
			gameevents->AddListener(this, it, false);
		}
	}

	~EventListener()
	{
		gameevents->RemoveListener(this);
	}

	void FireGameEvent(IGameEvent* event)
	{
		Aimbot::FireGameEvent(event);
		Hitmarkers::FireGameEvent(event);
		Resolver::FireGameEvent(event);
		Spammer::FireGameEvent(event);
		ValveDSCheck::FireGameEvent(event);
	}

	int GetEventDebugID() override
	{
		return EVENT_DEBUG_ID_INIT;
	}
};
