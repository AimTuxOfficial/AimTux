#include "atgui.h"

void SetupUI ()
{
	// Main window
	main_window = new MainWindow ("AimTux", Vector2D (270, 350), Vector2D (100, 100), Color (0, 0, 0, 0));
	gui->AddWindow (main_window);
	
	// Aimbot window
	
	
	
	gui->Focus (main_window);
}