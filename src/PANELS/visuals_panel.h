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
	ToggleSwitch* ts_weapon;
	ToggleSwitch* ts_color_code;
	ToggleSwitch* ts_bones;
	ToggleSwitch* ts_visibility_check;
	ToggleSwitch* ts_friendly;
	Banner*	ba_crosshair;
	ToggleSwitch* ts_recoil_crosshair;
	ToggleSwitch* ts_recoil_crosshair_shooting;
	ToggleSwitch* ts_fov_crosshair;
	Banner*	ba_chams;
	ToggleSwitch* ts_chams_players;
	ToggleSwitch* ts_chams_arms;
	ToggleSwitch* ts_chams_visibility_check;
	Banner*	ba_other;
	ToggleSwitch* ts_bomb;
	ToggleSwitch* ts_weapons;
	ToggleSwitch* ts_glow;
	ToggleSwitch* ts_dlights;
	Slider* sl_dlights;
	ToggleSwitch* ts_view_norecoil;
	ToggleSwitch* ts_show_scope_border;
	ComboBox<WallBoxType>* cb_wallstype;
	ComboBox<ChamsType>* cb_chamstype;
	ComboBox<ArmsType>* cb_armstype;
	ComboBox<TracerType>* cb_tracertype;
public:
	VisualsPanel (Vector2D position, Vector2D size);
};
