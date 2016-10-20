#include "atgui.h"

void SetupUI()
{
	int x, y;
	engine->GetScreenSize(x, y);
	
	// Main window
	main_window = new MainWindow("AimTux [NEW UI IN DEVELOPMENT]", LOC(1280-20, 720-20), LOC(10, 10), Color(0, 0, 0, 0));
	gui->AddWindow(main_window);

	// Menu window
	menu_window = new MenuWindow("AimTux", LOC(270, 450), LOC(100, 100), Color(0, 0, 0, 0));
	menu_window->position = LOC(x - menu_window->size.x - 10, 10);
	gui->AddWindow(menu_window);
	
	gui->Focus(menu_window);
}
