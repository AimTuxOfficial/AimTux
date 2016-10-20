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
public:
	HVHPanel (Vector2D position, Vector2D size);
};