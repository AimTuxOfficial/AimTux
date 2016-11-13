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
	StackedListBox<WallBoxType>* lb_wallstype;
	ToggleSwitch* ts_tracer;
	ToggleSwitch* ts_name;
	ToggleSwitch* ts_health;
	ToggleSwitch* ts_color_code;
	ToggleSwitch* ts_bones;
	ToggleSwitch* ts_visibility_check;
	ToggleSwitch* ts_friendly;
	Banner*	ba_crosshair;
	ToggleSwitch* ts_recoil_crosshair;
	ToggleSwitch* ts_fov_crosshair;
	Banner*	ba_chams;
	ToggleSwitch* ts_chams_players;
	ToggleSwitch* ts_chams_arms;
	StackedListBox<ArmsType>* lb_armstype;
	ToggleSwitch* ts_chams_visibility_check;
	StackedListBox<ChamsType>* lb_chamstype;
	Banner*	ba_other;
	ToggleSwitch* ts_bomb;
	ToggleSwitch* ts_weapons;
	ToggleSwitch* ts_glow;
	ToggleSwitch* ts_dlights;
	Slider* sl_dlights;
	ToggleSwitch* ts_view_norecoil;
public:
	VisualsPanel (Vector2D position, Vector2D size);
};
