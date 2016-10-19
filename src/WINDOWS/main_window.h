#ifndef __MAIN_WINDOW_H_
#define __MAIN_WINDOW_H_

class MainWindow;

#include "../UI/stdui.h"
#include "../atgui.h"

class MainWindow : public Window
{
private:
	ToggleSwitch* ts_bhop;
	ToggleSwitch* ts_autostrafe;
public:
	MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};

#endif
