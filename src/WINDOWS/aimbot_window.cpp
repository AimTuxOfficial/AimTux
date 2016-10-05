#include "aimbot_window.h"

AimbotWindow* aimbot_window = nullptr;

AimbotWindow::AimbotWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	Hide ();
}