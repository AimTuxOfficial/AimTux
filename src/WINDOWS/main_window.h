#ifndef __MAIN_WINDOW_H_
#define __MAIN_WINDOW_H_

class MainWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class MainWindow : public Window
{
private:
	ToggleButton* aimbot_button;
	ToggleButton* triggerbot_button;
	ToggleButton* esp_button;
	ToggleButton* hvh_button;
	ToggleButton* misc_button;
	Button* load1_button;
	Button* load2_button;
	Button* save1_button;
	Button* save2_button;

	void load1_button_clicked ();
	void load2_button_clicked ();
	void save1_button_clicked ();
	void save2_button_clicked ();

public:
	MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};

#endif