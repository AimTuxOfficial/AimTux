#include "aimbot_window.h"

TriggerbotWindow* triggerbot_window = nullptr;

TriggerbotWindow::TriggerbotWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_triggerbot_enabled = new ToggleSwitch ("triggerbot", Vector2D (10, 10), 33, &Settings::Triggerbot::enabled);
	AddComponent (ts_triggerbot_enabled);

	ts_delay = new ToggleSwitch ("delay", BELOW (ts_triggerbot_enabled), 33, &Settings::Triggerbot::Delay::enabled);
	AddComponent (ts_delay);

	sl_delay = new Slider ("", STACK (ts_delay), Vector2D (size.x - ts_delay->size.x - 30, 33), &Settings::Triggerbot::Delay::value, 0.0f, 1000.0f);
	AddComponent (sl_delay);

	ba_filter = new Banner ("Filter", BELOW (ts_delay), size.x - 20);
	AddComponent (ba_filter);

	ts_friendly = new ToggleSwitch ("friendly", BELOW (ba_filter), 33, &Settings::Triggerbot::Filter::friendly);
	AddComponent (ts_friendly);

	ts_head = new ToggleSwitch ("head", BELOW (ts_friendly), 33, &Settings::Triggerbot::Filter::head);
	AddComponent (ts_head);

	ts_chest = new ToggleSwitch ("chest", BELOW (ts_head), 33, &Settings::Triggerbot::Filter::chest);
	AddComponent (ts_chest);

	ts_arms = new ToggleSwitch ("arms", BELOW (ts_chest), 33, &Settings::Triggerbot::Filter::arms);
	AddComponent (ts_arms);

	ts_legs = new ToggleSwitch ("legs", BELOW (ts_arms), 33, &Settings::Triggerbot::Filter::legs);
	AddComponent (ts_legs);

	Hide ();
}