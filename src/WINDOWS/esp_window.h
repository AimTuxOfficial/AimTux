#ifndef __ESP_WINDOW_H_
#define __ESP_WINDOW_H_

class ESPWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class ESPWindow : public Window
{
private:
	ToggleSwitch* ts_esp_enabled;
	ToggleSwitch* ts_visibility_check;
	ToggleSwitch* ts_walls;
	ToggleSwitch* ts_tracer;
	ToggleSwitch* ts_name;
	ToggleSwitch* ts_health;
	ToggleSwitch* ts_bones;
	ToggleSwitch* ts_chams_players;
	ToggleSwitch* ts_chams_arms;
	ToggleSwitch* ts_recoil_crosshair;
public:
	ESPWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};

#endif