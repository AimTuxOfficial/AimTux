#include "triggerbot_panel.h"

TriggerbotPanel::TriggerbotPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_triggerbot_enabled = new ToggleSwitch ("Enabled", LOC (10, 10), LOC((size.x - 20) / 6.75, 30), &cSettings.Triggerbot.enabled);
	AddComponent (ts_triggerbot_enabled);

	kb_triggerbot_key =  new KeyBind ("Trigger Key", BELOW (ts_triggerbot_enabled), LOC((size.x - 20) / 6.75, 30),  &cSettings.Triggerbot.key);
	AddComponent(kb_triggerbot_key);

	ba_delay = new Banner ("Delay", BELOW (kb_triggerbot_key), (size.x - 20) / 2 - 5);
	AddComponent (ba_delay);

	ts_delay = new ToggleSwitch ("Enabled", BELOW (ba_delay), LOC((size.x - 20) / 6.75, 30), &cSettings.Triggerbot.Delay.enabled);
	AddComponent (ts_delay);

	sl_delay = new Slider_INT ("(ms)", STACK (ts_delay), LOC ((size.x / 2) - ts_delay->size.x - 30, 33), &cSettings.Triggerbot.Delay.value, 0.0f, 1000.0f);
	AddComponent (sl_delay);

	ba_filter = new Banner ("Filter", BELOW (ts_delay), (size.x - 20) / 2 - 5);
	AddComponent (ba_filter);

	ts_friendly = new ToggleSwitch ("Friendly", BELOW (ba_filter), LOC((size.x - 20) / 6.75, 30), &cSettings.Triggerbot.Filter.friendly);
	AddComponent (ts_friendly);

	ts_head = new ToggleSwitch ("Head", BELOW (ts_friendly), LOC((size.x - 20) / 6.75, 30), &cSettings.Triggerbot.Filter.head);
	AddComponent (ts_head);

	ts_chest = new ToggleSwitch ("Chest", BELOW (ts_head), LOC((size.x - 20) / 6.75, 30), &cSettings.Triggerbot.Filter.chest);
	AddComponent (ts_chest);

	ts_arms = new ToggleSwitch ("Arms", BELOW (ts_chest), LOC((size.x - 20) / 6.75, 30), &cSettings.Triggerbot.Filter.arms);
	AddComponent (ts_arms);

	ts_legs = new ToggleSwitch ("Legs", BELOW (ts_arms), LOC((size.x - 20) / 6.75, 30), &cSettings.Triggerbot.Filter.legs);
	AddComponent (ts_legs);

	Hide ();
}
