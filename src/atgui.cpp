#include "atgui.h"

void SetupUI ()
{
	// Main window
	main_window = new MainWindow ("AimTux", Vector2D (270, 350), Vector2D (100, 100), Color (0, 0, 0, 0));
	gui->AddWindow (main_window);
	
	// Aimbot window
	aimbot_window = new AimbotWindow ("Aimbot", Vector2D (700, 600), Vector2D (400, 400), Color (0, 0, 0, 0));
	gui->AddWindow (aimbot_window);
	
	
	gui->Focus (main_window);
}