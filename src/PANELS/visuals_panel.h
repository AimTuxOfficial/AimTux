#pragma once

class VisualsPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class VisualsPanel : public Panel
{
private:
	ToggleSwitch* ts_esp_enabled;
	Banner*	ba_esp;
	ToggleSwitch* ts_walls;
	ToggleSwitch* ts_tracer;
	ToggleSwitch* ts_name;
	ToggleSwitch* ts_health;
	ToggleSwitch* ts_bones;
	ToggleSwitch* ts_visibility_check;
	Banner*	ba_crosshair;
	ToggleSwitch* ts_recoil_crosshair;
	ToggleSwitch* ts_fov_crosshair;
	Banner*	ba_other;
	ToggleSwitch* ts_bomb;
	ToggleSwitch* ts_weapons;
	Banner*	ba_chams;
	ToggleSwitch* ts_chams_players;
	ToggleSwitch* ts_chams_arms;
	ToggleSwitch* ts_rainbow_chams_hands;
	ToggleSwitch* ts_visibility_check_chams;
	StackedListBox<ChamsType>* lb_chamstype;
public:
	VisualsPanel (Vector2D position, Vector2D size);
};