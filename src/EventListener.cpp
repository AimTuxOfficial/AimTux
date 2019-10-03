#include "EventListener.h"

#include "Hacks/aimbot.h"
#include "Hacks/eventlog.h"
#include "Hacks/hitmarkers.h"
#include "Hacks/namestealer.h"
#include "Hacks/resolver.h"
#include "Hacks/skinchanger.h"
#include "Hacks/spammer.h"
#include "Hacks/valvedscheck.h"
#include "interfaces.h"
#include "SDK/IGameEvent.h"

EventListener::EventListener(std::vector<const char*> events)
{
    for (const auto& it : events)
	gameEvents->AddListener(this, it, false);
}

EventListener::~EventListener()
{
    gameEvents->RemoveListener(this);
}

void EventListener::FireGameEvent(IGameEvent* event)
{
    Aimbot::FireGameEvent(event);
    Hitmarkers::FireGameEvent(event);
    Eventlog::FireGameEvent(event);
    NameStealer::FireGameEvent(event);
    Resolver::FireGameEvent(event);
    Spammer::FireGameEvent(event);
    ValveDSCheck::FireGameEvent(event);
    SkinChanger::FireGameEvent(event);
}

int EventListener::GetEventDebugID()
{
    return EVENT_DEBUG_ID_INIT;
}
