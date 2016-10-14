#ifndef __HVH_WINDOW_H_
#define __HVH_WINDOW_H_

class HVHWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class HVHWindow : public Window
{
private:
	ListBox<AntiAimType_X>* lb_antiaim_x;
	ToggleSwitch* ts_antiaim_x;
	ListBox<AntiAimType_Y>* lb_antiaim_y;
	ToggleSwitch* ts_antiaim_y;
public:
	HVHWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};

#endif