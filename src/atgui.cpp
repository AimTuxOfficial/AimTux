#include "atgui.h"

void SetupUI()
{
	int x, y;
	engine->GetScreenSize(x, y);

	// Main window
	main_window = new MainWindow("AimTux Settings", LOC(1280 - 20, 720 - 20), LOC((x / 2) - (1280 - 20) / 2, (y / 2) - (720 - 20) / 2), Color(0, 0, 0, 0));
	gui->AddWindow(main_window);

	// Menu window
	config_window = new ConfigWindow("Configs", LOC(270, 140), LOC(100, 100), Color(0, 0, 0, 0));
	config_window->position = LOC(x - 10 - 270, y - 10 - 140);
	gui->AddWindow(config_window);

	gui->Focus(config_window);
}
