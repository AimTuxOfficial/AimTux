#include "triggerbot_panel.h"

TriggerbotPanel::TriggerbotPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_triggerbot_enabled = new ToggleSwitch ("enabled", LOC (10, 10), 33, &Settings::Triggerbot::enabled);
	AddComponent (ts_triggerbot_enabled);

	kb_triggerbot_key =  new KeyBind ("key", BELOW (ts_triggerbot_enabled), LOC (220, 33),  &Settings::Triggerbot::key);
	AddComponent(kb_triggerbot_key);

	ba_delay = new Banner ("Delay", BELOW (kb_triggerbot_key), (size.x - 20) / 2 - 5);
	AddComponent (ba_delay);

	ts_delay = new ToggleSwitch ("delay", BELOW (ba_delay), 33, &Settings::Triggerbot::Delay::enabled);
	AddComponent (ts_delay);

	sl_delay = new Slider_INT ("", STACK (ts_delay), LOC ((size.x / 2) - ts_delay->size.x - 30, 33), &Settings::Triggerbot::Delay::value, 0.0f, 1000.0f);
	AddComponent (sl_delay);

	ba_filter = new Banner ("Filter", BELOW (ts_delay), (size.x - 20) / 2 - 5);
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
