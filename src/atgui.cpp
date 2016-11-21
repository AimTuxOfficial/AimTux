#include "atgui.h"

void SetupUI()
{
	int x, y;
	engine->GetScreenSize(x, y);

	// Main window
	main_window = new MainWindow("AimTux Settings", LOC(1280 - 20, 720 - 20), LOC((x / 2) - (1280 - 20) / 2, (y / 2) - (720 - 20) / 2), Color(0, 0, 0, 0));
	gui->AddWindow(main_window);

	gui->Focus(main_window);
}
