#pragma once

class AimbotPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class AimbotPanel : public Panel
{
private:
	ToggleSwitch* ts_aimbot_enabled;
	Banner* ba_aim;
	ToggleSwitch* ts_silent;
	ToggleSwitch* ts_rcs;
	ToggleSwitch* ts_autoaim;
	Slider* sl_fov;
	Slider* sl_error;
	ToggleSwitch* ts_smooth;
	Slider* sl_smooth;
	ToggleSwitch* ts_aimstep;
	Slider* sl_aimstep;
	ToggleSwitch* ts_autowall;
	Slider* sl_autowall;
	ToggleSwitch* ts_autoshoot;
	Banner* ba_movement;
	ToggleSwitch* ts_autocrouch;
	ToggleSwitch* ts_autostop;
	Banner* ba_target;
	ToggleSwitch* ts_friendly;
	StackedListBox<Bones>* lb_aimbone;
public:
	AimbotPanel (Vector2D position, Vector2D size);
};
