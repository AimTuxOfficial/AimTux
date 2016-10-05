#include "esp_window.h"

ESPWindow* esp_window = nullptr;

ESPWindow::ESPWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_esp_enabled = new ToggleSwitch ("esp", LOC (10, 10), LOC (120, 35), &Settings::ESP::enabled);
	AddComponent (ts_esp_enabled);
	
	ts_visibility_check = new ToggleSwitch ("visibility check", LOC (10, ts_esp_enabled->position.y + ts_esp_enabled->size.y + 10), LOC (170, 35), &Settings::ESP::visibility_check);
	AddComponent (ts_visibility_check);
	
	ts_walls = new ToggleSwitch ("walls", LOC (10, ts_visibility_check->position.y + ts_visibility_check->size.y + 10), LOC (150, 35), &Settings::ESP::Walls::enabled);
	AddComponent (ts_walls);
	
	ts_tracer = new ToggleSwitch ("tracer", LOC (10, ts_walls->position.y + ts_walls->size.y + 10), LOC (150, 35), &Settings::ESP::Tracer::enabled);
	AddComponent (ts_tracer);
	
	ts_name = new ToggleSwitch ("show name", LOC (10, ts_tracer->position.y + ts_tracer->size.y + 10), LOC (145, 35), &Settings::ESP::Name::enabled);
	AddComponent (ts_name);
	
	ts_bones = new ToggleSwitch ("show bones", LOC (10, ts_name->position.y + ts_name->size.y + 10), LOC (160, 35), &Settings::ESP::Bones::enabled);
	AddComponent (ts_bones);
	
	Hide ();
}