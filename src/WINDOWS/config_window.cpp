#include "config_window.h"

ConfigWindow* config_window = nullptr;

ConfigWindow::ConfigWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, true)
{
	Show ();
}