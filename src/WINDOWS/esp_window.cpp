#include "esp_window.h"

ESPWindow* esp_window = nullptr;

ESPWindow::ESPWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_esp_enabled = new ToggleSwitch ("esp", LOC (10, 10), 35, &Settings::ESP::enabled);
	AddComponent (ts_esp_enabled);
	
	ba_player_info = new Banner ("Player Visuals", BELOW (ts_esp_enabled), size.x - 20);
	AddComponent (ba_player_info);
	
	ts_walls = new ToggleSwitch ("walls", BELOW (ba_player_info), 35, &Settings::ESP::Walls::enabled);
	AddComponent (ts_walls);
	
	ts_tracer = new ToggleSwitch ("tracer", BELOW (ts_walls), 35, &Settings::ESP::Tracer::enabled);
	AddComponent (ts_tracer);
	
	ts_name = new ToggleSwitch ("show name", BELOW (ts_tracer), 35, &Settings::ESP::Info::showName);
	AddComponent (ts_name);
	
	ts_health = new ToggleSwitch ("show health", BELOW (ts_name), 35, &Settings::ESP::Info::showHealth);
	AddComponent (ts_health);
	
	ts_bones = new ToggleSwitch ("show bones", BELOW (ts_health), 35, &Settings::ESP::Bones::enabled);
	AddComponent (ts_bones);
	
	ts_visibility_check = new ToggleSwitch ("visibility check", BELOW (ts_bones), 35, &Settings::ESP::visibility_check);
	AddComponent (ts_visibility_check);
	
	ba_chams = new Banner ("Chams", BELOW (ts_visibility_check), size.x - 20);
	AddComponent (ba_chams);
	
	ts_chams_players = new ToggleSwitch ("players", BELOW (ba_chams), 35, &Settings::ESP::Chams::players);
	AddComponent (ts_chams_players);
	
	ts_chams_arms = new ToggleSwitch ("arms", STACK (ts_chams_players), 35, &Settings::ESP::Chams::arms);
	AddComponent (ts_chams_arms);

	ts_rainbow_chams_hands = new ToggleSwitch ("rainbow arms", STACK (ts_chams_arms), 35, &Settings::ESP::Chams::rainbow_arms);
	AddComponent (ts_rainbow_chams_hands);

	ts_visibility_check_chams = new ToggleSwitch ("visibility check", STACK (ts_rainbow_chams_hands), 35, &Settings::ESP::Chams::visibility_check);
	AddComponent (ts_visibility_check_chams);
	
	ba_crosshair = new Banner ("Crosshair", BELOW (ts_visibility_check_chams), size.x - 20);
	AddComponent (ba_crosshair);
	
	ts_recoil_crosshair = new ToggleSwitch ("recoil crosshair", BELOW (ba_crosshair), 35, &Settings::Recoilcrosshair::enabled);
	AddComponent (ts_recoil_crosshair);
	
	ts_fov_crosshair = new ToggleSwitch ("fov crosshair", STACK (ts_recoil_crosshair), 35, &Settings::ESP::FOVCrosshair::enabled);
	AddComponent (ts_fov_crosshair);
	
	ba_other = new Banner ("Other", BELOW (ts_fov_crosshair), size.x - 20);
	AddComponent (ba_other);
	
	ts_bomb = new ToggleSwitch ("bomb esp", BELOW (ba_other), 35, &Settings::ESP::Bomb::enabled);
	AddComponent (ts_bomb);

	ts_weapons = new ToggleSwitch ("weapons esp", STACK (ts_bomb), 35, &Settings::ESP::Weapons::enabled);
	AddComponent (ts_weapons);
	
	Hide ();
}