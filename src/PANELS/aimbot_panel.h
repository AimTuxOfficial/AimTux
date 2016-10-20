#pragma once

class AimbotPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class AimbotPanel : public Panel
{
private:
	ToggleSwitch* ts_aimbot_enabled;
	ToggleSwitch* ts_silent;
	ToggleSwitch* ts_friendly;
	Banner* ba_aim;
	ToggleSwitch* ts_autoaim;
	Slider*	sl_fov;
	StackedListBox<Bones>* lb_aimbone;
	ToggleSwitch* ts_smooth_enable;
	Slider* sl_smooth_value;
	ToggleSwitch* ts_rcs;
	ToggleSwitch* ts_aimstep;
	ToggleSwitch* ts_autoshoot;
	Banner* ba_movement;
	ToggleSwitch* ts_autocrouch;
	ToggleSwitch* ts_autostop;
public:
	AimbotPanel (Vector2D position, Vector2D size);
};