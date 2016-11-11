#include "atgui.h"

void SetupUI()
{
	int x, y;
	engine->GetScreenSize(x, y);

	// Main window
	main_window = new MainWindow("AimTux Settings", LOC(1000, 720 - 20), LOC((x / 2) - (1000) / 2, (y / 2) - (720 - 20) / 2), Color(0, 0, 0, 0));
	gui->AddWindow(main_window);

	// Menu window
	menu_window = new MenuWindow("Configs", LOC(270, 150), LOC(100, 100), Color(0, 0, 0, 0));
	menu_window->position = LOC(x - 10 - 270, y - 10 - 150);
	gui->AddWindow(menu_window);

	skinchange_window = new SkinChangeWindow("Skin Changer", LOC(750, 250), LOC(100, 100), Color(0, 0, 0, 0));
	skinchange_window->position = LOC(10, 10);
	gui->AddWindow(skinchange_window);

	gui->Focus(main_window);
}
