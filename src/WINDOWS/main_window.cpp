#include "main_window.h"

MainWindow* main_window = nullptr;

MainWindow::MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, false)
{
	ts_bhop = new ToggleSwitch ("bhop", LOC (10, 10), 33, &Settings::BHop::enabled);
	AddComponent (ts_bhop);
	
	ts_autostrafe = new ToggleSwitch ("auto strafe", BELOW (ts_bhop), 33, &Settings::AutoStrafe::enabled);
	AddComponent (ts_autostrafe);
	
	Hide ();
}
