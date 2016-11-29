#pragma once

class HVHPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class HVHPanel : public Panel
{
private:

	Banner* ba_antiaim;
	ComboBox<AntiAimType_X>* cb_antiaim_x;
	ToggleSwitch* ts_antiaim_x;
	ComboBox<AntiAimType_Y>* cb_antiaim_y;
	ToggleSwitch* ts_antiaim_y;
	Banner* ba_movement;
	ToggleSwitch* ts_autocrouch;
	ToggleSwitch* ts_autostop;
	ToggleSwitch* ts_edge_hide;
	Slider* sl_edge_distance;


	Banner* ba_autowall;
	ToggleSwitch* ts_autowall;
	Slider* sl_autowall;
	MS_ListBox<Hitbox>* lb_bone_select_multi;
public:
	HVHPanel (Vector2D position, Vector2D size);
};
