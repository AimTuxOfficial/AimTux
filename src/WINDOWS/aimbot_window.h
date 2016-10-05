#ifndef __AIMBOT_WINDOW_H_
#define __AIMBOT_WINDOW_H_

class AimbotWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class AimbotWindow : public Window
{
private:
	ToggleSwitch* ts_aimbot_enabled;
public:
	AimbotWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};

#endif