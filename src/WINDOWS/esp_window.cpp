#include "esp_window.h"

ESPWindow* esp_window = nullptr;

ESPWindow::ESPWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_esp_enabled = new ToggleSwitch ("esp", LOC (10, 10), 35, &Settings::ESP::enabled);
	AddComponent (ts_esp_enabled);
	
	ts_visibility_check = new ToggleSwitch ("visibility check", LOC (10, ts_esp_enabled->position.y + ts_esp_enabled->size.y + 10), 35, &Settings::ESP::visibility_check);
	AddComponent (ts_visibility_check);
	
	ts_walls = new ToggleSwitch ("walls", LOC (10, ts_visibility_check->position.y + ts_visibility_check->size.y + 10), 35, &Settings::ESP::Walls::enabled);
	AddComponent (ts_walls);
	
	ts_tracer = new ToggleSwitch ("tracer", LOC (10, ts_walls->position.y + ts_walls->size.y + 10), 35, &Settings::ESP::Tracer::enabled);
	AddComponent (ts_tracer);
	
	ts_name = new ToggleSwitch ("show name", LOC (10, ts_tracer->position.y + ts_tracer->size.y + 10), 35, &Settings::ESP::Info::showName);
	AddComponent (ts_name);
	
	ts_health = new ToggleSwitch ("show health", LOC (10, ts_name->position.y + ts_name->size.y + 10), 35, &Settings::ESP::Info::showHealth);
	AddComponent (ts_health);
	
	ts_bones = new ToggleSwitch ("show bones", LOC (10, ts_health->position.y + ts_health->size.y + 10), 35, &Settings::ESP::Bones::enabled);
	AddComponent (ts_bones);
	
	ts_chams_players = new ToggleSwitch ("player chams", LOC (10, ts_bones->position.y + ts_bones->size.y + 10), 35, &Settings::ESP::Chams::players);
	AddComponent (ts_chams_players);
	
	ts_chams_arms = new ToggleSwitch ("cham arms", LOC (10, ts_chams_players->position.y + ts_chams_players->size.y + 10), 35, &Settings::ESP::Chams::arms);
	AddComponent (ts_chams_arms);
	
	Hide ();
}