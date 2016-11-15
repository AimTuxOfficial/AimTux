#include "triggerbot_panel.h"

TriggerbotPanel::TriggerbotPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_triggerbot_enabled = new ToggleSwitchTip ("Enabled", LOC (10, 10), LOC((size.x - 20) / 6.75, 30), &Settings::Triggerbot::enabled, "Enables or disables the Triggerbot");
	kb_triggerbot_key =  new KeyBind ("Trigger Key", BELOW (ts_triggerbot_enabled), LOC((size.x - 20) / 6.75, 30),  &Settings::Triggerbot::key);
	ba_delay = new Banner ("Delay", BELOW (kb_triggerbot_key), (size.x - 20) / 2 - 5);
	ts_delay = new ToggleSwitchTip ("Enabled", BELOW (ba_delay), LOC((size.x - 20) / 6.75, 30), &Settings::Triggerbot::Delay::enabled, "Trigger delay when trigger key is held");
	sl_delay = new Slider_INT ("(ms)", STACK (ts_delay), LOC ((size.x / 2) - ts_delay->size.x - 30, 33), &Settings::Triggerbot::Delay::value, 0.0f, 1000.0f);
	ba_filter = new Banner ("Filter", BELOW (ts_delay), (size.x - 20) / 2 - 5);
	ts_friendly = new ToggleSwitchTip ("Friendly", BELOW (ba_filter), LOC((size.x - 20) / 6.75, 30), &Settings::Triggerbot::Filter::friendly, "Enable triggerbot to target allies");
	ts_head = new ToggleSwitchTip ("Head", BELOW (ts_friendly), LOC((size.x - 20) / 6.75, 30), &Settings::Triggerbot::Filter::head, "Triggerbot will target the head");
	ts_chest = new ToggleSwitchTip ("Chest", BELOW (ts_head), LOC((size.x - 20) / 6.75, 30), &Settings::Triggerbot::Filter::chest, "Triggerbot will target the chest");
	ts_arms = new ToggleSwitchTip ("Arms", BELOW (ts_chest), LOC((size.x - 20) / 6.75, 30), &Settings::Triggerbot::Filter::arms, "Triggerbot will target the arms");
	ts_legs = new ToggleSwitchTip ("Legs", BELOW (ts_arms), LOC((size.x - 20) / 6.75, 30), &Settings::Triggerbot::Filter::legs, "Triggerbot will target the legs");
	
	AddComponent (ts_legs);
	AddComponent (ts_arms);
	AddComponent (ts_chest);
	AddComponent (ts_head);
	AddComponent (ts_friendly);
	AddComponent (ba_filter);
	AddComponent (sl_delay);
	AddComponent (ts_delay);
	AddComponent (ba_delay);
	AddComponent(kb_triggerbot_key);
	AddComponent (ts_triggerbot_enabled);

	Hide ();
}
