#include "atgui.h"

void SetupUI()
{
	int x, y;
	engine->GetScreenSize(x, y);
	
	// ESP window
	esp_window = new ESPWindow("Visuals", LOC(575, 640), LOC(10, 10), Color(0, 0, 0, 0));
	gui->AddWindow(esp_window);

	// HVH window
	hvh_window = new HVHWindow("Hack vs Hack", LOC(370, 410), LOC(10, 10), Color(0, 0, 0, 0));
	gui->AddWindow(hvh_window);

	// Misc window
	misc_window = new MiscWindow("Miscellaneous", LOC(575, 410), LOC(10, 660), Color(0, 0, 0, 0));
	gui->AddWindow(misc_window);

	// Main window
	main_window = new MainWindow("AimTux [NEW UI IN DEVELOPMENT]", LOC(1900, 1060), LOC(10, 10), Color(0, 0, 0, 0));
	gui->AddWindow(main_window);

	// Menu window
	menu_window = new MenuWindow("AimTux", LOC(270, 450), LOC(100, 100), Color(0, 0, 0, 0));
	menu_window->position = LOC(x - menu_window->size.x - 10, 10);
	gui->AddWindow(menu_window);
	
	gui->Focus(menu_window);
}
