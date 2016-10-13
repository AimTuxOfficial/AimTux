#ifndef __HVH_WINDOW_H_
#define __HVH_WINDOW_H_

class HVHWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class HVHWindow : public Window
{
private:
	ListBox<AntiAimType_X>* lb_spin_x;
	ToggleSwitch* ts_spin_x;
	ListBox<AntiAimType_Y>* lb_spin_y;
	ToggleSwitch* ts_spin_y;
public:
	HVHWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};

#endif