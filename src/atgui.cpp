#include "atgui.h"

void SetupUI()
{
	int x, y;
	engine->GetScreenSize(x, y);

	// Aimbot window
	aimbot_window = new AimbotWindow("Aimbot", Vector2D(670, 600), Vector2D(595, 10), Color(0, 0, 0, 0));
	gui->AddWindow(aimbot_window);

	// ESP window
	esp_window = new ESPWindow("Visuals", Vector2D(575, 650), Vector2D(10, 10), Color(0, 0, 0, 0));
	gui->AddWindow(esp_window);

	// HVH window
	hvh_window = new HVHWindow("Hack vs Hack", Vector2D(370, 450), Vector2D(aimbot_window->position.x, aimbot_window->position.y + aimbot_window->size.y + 10), Color(0, 0, 0, 0));
	gui->AddWindow(hvh_window);

	// Triggerbot window
	triggerbot_window = new TriggerbotWindow("Triggerbot", Vector2D(290, 450), Vector2D(hvh_window->position.x + hvh_window->size.x + 10, hvh_window->position.y), Color(0, 0, 0, 0));
	gui->AddWindow(triggerbot_window);
	
	// Misc window
	misc_window = new MiscWindow("Miscellaneous", Vector2D(580, 400), Vector2D(10, 670), Color(0, 0, 0, 0));
	gui->AddWindow(misc_window);
	
	// Main window
	main_window = new MainWindow("AimTux", Vector2D(270, 400), Vector2D(100, 100), Color(0, 0, 0, 0));
	main_window->position = Vector2D(x - main_window->size.x - 10, 10);
	gui->AddWindow(main_window);
	
	gui->Focus(main_window);
}