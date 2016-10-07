#include "hvh_window.h"

HVHWindow* hvh_window = nullptr;

HVHWindow::HVHWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_spin_x = new ToggleSwitch ("spin x", LOC (10, 10), 35, &Settings::AntiAim::enabled_X);
	AddComponent (ts_spin_x);
	
	ts_spin_y = new ToggleSwitch ("spin y", LOC (10, ts_spin_x->position.y + ts_spin_x->size.y + 10), 35, &Settings::AntiAim::enabled_Y);
	AddComponent (ts_spin_y);
	Hide ();
}
