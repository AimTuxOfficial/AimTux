#pragma once

class ESPPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class ESPPanel : public Panel
{
private:
	ToggleSwitch* ts_esp_enabled;
	ToggleSwitch* ts_visibility_check;
	Banner*	ba_player_info;
	ToggleSwitch* ts_walls;
	ToggleSwitch* ts_tracer;
	ToggleSwitch* ts_name;
	ToggleSwitch* ts_health;
	ToggleSwitch* ts_bones;
	Banner*	ba_chams;
	ToggleSwitch* ts_chams_players;
	ToggleSwitch* ts_chams_arms;
	ToggleSwitch* ts_rainbow_chams_hands;
	ToggleSwitch* ts_visibility_check_chams;
	Banner*	ba_crosshair;
	ToggleSwitch* ts_recoil_crosshair;
	ToggleSwitch* ts_fov_crosshair;
	Banner*	ba_other;
	ToggleSwitch* ts_bomb;
	ToggleSwitch* ts_weapons;
public:
	ESPPanel (Vector2D position, Vector2D size);
};