#include "main_window.h"

MainWindow* main_window = nullptr;

MainWindow::MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	aimbot_button = new OutlinedButton ("AimBot", LOC (10, 10), LOC (size.x-20, 40));
	AddComponent (aimbot_button);
	
	esp_button = new OutlinedButton ("ESP", LOC (10, 60), LOC (size.x-20, 40));
	AddComponent (esp_button);
	
	Show ();
}