#pragma once

class AimbotPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class AimbotPanel : public Panel
{
private:
	ToggleSwitch* ts_aimbot_enabled;
	Banner* ba_aim;
	KeyBind* kb_aimkey;
	ToggleSwitch* ts_aimkey_only;
	ToggleSwitch* ts_silent;
	ToggleSwitch* ts_rcs;
	Slider* sl_rcs;
	ToggleSwitch* ts_autoaim;
	Slider* sl_fov;
	ToggleSwitch* ts_salting;
	Slider* sl_salting;
	ToggleSwitch* ts_smooth;
	Slider* sl_smooth;
	ToggleSwitch* ts_aimstep;
	Slider* sl_aimstep;
	Slider* sl_error;
	ToggleSwitch* ts_autopistol;
	ToggleSwitch* ts_autoshoot;
	ToggleSwitch* ts_autoscope;
	Banner* ba_movement;
	ToggleSwitch* ts_autocrouch;
	ToggleSwitch* ts_autostop;
	Banner* ba_target;
	ToggleSwitch* ts_friendly;
	StackedListBox<Bone>* lb_aimbone;
public:
	AimbotPanel (Vector2D position, Vector2D size);
};
