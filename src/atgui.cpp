#include "atgui.h"

void SetupUI()
{
	int x, y;
	engine->GetScreenSize(x, y);

	// Aimbot window
	aimbot_window = new AimbotWindow("Aimbot", LOC(670, 640), LOC(595, 10), Color(0, 0, 0, 0));
	gui->AddWindow(aimbot_window);

	// ESP window
	esp_window = new ESPWindow("Visuals", LOC(575, 640), LOC(10, 10), Color(0, 0, 0, 0));
	gui->AddWindow(esp_window);

	// HVH window
	hvh_window = new HVHWindow("Hack vs Hack", LOC(370, 410), LOC(aimbot_window->position.x, aimbot_window->position.y + aimbot_window->size.y + 10), Color(0, 0, 0, 0));
	gui->AddWindow(hvh_window);

	// Triggerbot window
	triggerbot_window = new TriggerbotWindow("Triggerbot", LOC(290, 410), LOC(hvh_window->position.x + hvh_window->size.x + 10, hvh_window->position.y), Color(0, 0, 0, 0));
	gui->AddWindow(triggerbot_window);
	
	// Misc window
	misc_window = new MiscWindow("Miscellaneous", LOC(575, 410), LOC(10, 660), Color(0, 0, 0, 0));
	gui->AddWindow(misc_window);

	// Main window
	main_window = new MainWindow("AimTux", LOC(270, 400), LOC(100, 100), Color(0, 0, 0, 0));
	main_window->position = LOC(x - main_window->size.x - 10, 10);
	gui->AddWindow(main_window);
	
	gui->Focus(main_window);
}