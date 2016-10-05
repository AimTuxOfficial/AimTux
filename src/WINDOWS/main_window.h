#ifndef __MAIN_WINDOW_H_
#define __MAIN_WINDOW_H_

class MainWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class MainWindow : public Window
{
private:
	Button* aimbot_button;
	Button* esp_button;
public:
	MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};

#endif