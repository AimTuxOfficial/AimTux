#pragma once

class AimbotWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class AimbotWindow : public Window
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
	ToggleSwitch* ts_autowall;
	Slider* sl_autowall_value;
	ToggleSwitch* ts_autocrouch;
	ToggleSwitch* ts_autostop;
public:
	AimbotWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};
