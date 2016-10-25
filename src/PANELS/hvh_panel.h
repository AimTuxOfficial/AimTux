#pragma once

class HVHPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class HVHPanel : public Panel
{
private:
	ListBox<AntiAimType_X>* lb_antiaim_x;
	ToggleSwitch* ts_antiaim_x;
	ListBox<AntiAimType_Y>* lb_antiaim_y;
	ToggleSwitch* ts_antiaim_y;
	MS_ListBox<Hitbox>* lb_bone_select_multi;
public:
	HVHPanel (Vector2D position, Vector2D size);
};
