#include "aimbot_window.h"

AimbotWindow* aimbot_window = nullptr;

AimbotWindow::AimbotWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_aimbot_enabled = new ToggleSwitch ("aimbot", LOC (10, 10), LOC (120, 35), &Settings::Aimbot::enabled);
	AddComponent (ts_aimbot_enabled);
	Hide ();
}