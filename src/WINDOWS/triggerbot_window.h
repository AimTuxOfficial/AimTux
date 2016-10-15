#ifndef __TRIGGERBOT_WINDOW_H_
#define __TRIGGERBOT_WINDOW_H_

class TriggerbotWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class TriggerbotWindow : public Window
{
private:
	ToggleSwitch* ts_triggerbot_enabled;
	ToggleSwitch* ts_hitchance;
	Slider*	sl_hitchance;
	Banner* ba_filter;
	ToggleSwitch* ts_friendly;
	ToggleSwitch* ts_head;
	ToggleSwitch* ts_chest;
	ToggleSwitch* ts_arms;
	ToggleSwitch* ts_legs;
public:
	TriggerbotWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};

#endif