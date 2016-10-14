#include "esp_window.h"

ESPWindow* esp_window = nullptr;

ESPWindow::ESPWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_esp_enabled = new ToggleSwitch ("esp", LOC (10, 10), 35, &Settings::ESP::enabled);
	AddComponent (ts_esp_enabled);
	
	ba_player_info = new Banner ("Player Visuals", LOC (10, ts_esp_enabled->position.y + ts_esp_enabled->size.y + 10), size.x - 20);
	AddComponent (ba_player_info);
	
	ts_walls = new ToggleSwitch ("walls", LOC (10, ba_player_info->position.y + ba_player_info->size.y + 10), 35, &Settings::ESP::Walls::enabled);
	AddComponent (ts_walls);
	
	ts_tracer = new ToggleSwitch ("tracer", LOC (10, ts_walls->position.y + ts_walls->size.y + 10), 35, &Settings::ESP::Tracer::enabled);
	AddComponent (ts_tracer);
	
	ts_name = new ToggleSwitch ("show name", LOC (10, ts_tracer->position.y + ts_tracer->size.y + 10), 35, &Settings::ESP::Info::showName);
	AddComponent (ts_name);
	
	ts_health = new ToggleSwitch ("show health", LOC (10, ts_name->position.y + ts_name->size.y + 10), 35, &Settings::ESP::Info::showHealth);
	AddComponent (ts_health);
	
	ts_bones = new ToggleSwitch ("show bones", LOC (10, ts_health->position.y + ts_health->size.y + 10), 35, &Settings::ESP::Bones::enabled);
	AddComponent (ts_bones);
	
	ts_visibility_check = new ToggleSwitch ("visibility check", LOC (10, ts_bones->position.y + ts_bones->size.y + 10), 35, &Settings::ESP::visibility_check);
	AddComponent (ts_visibility_check);
	
	ba_chams = new Banner ("Chams", LOC (10, ts_visibility_check->position.y + ts_visibility_check->size.y + 10), size.x - 20);
	AddComponent (ba_chams);
	
	ts_chams_players = new ToggleSwitch ("players", LOC (10, ba_chams->position.y + ba_chams->size.y + 10), 35, &Settings::ESP::Chams::players);
	AddComponent (ts_chams_players);
	
	ts_chams_arms = new ToggleSwitch ("arms", LOC (ts_chams_players->position.x + ts_chams_players->size.x + 10, ts_chams_players->position.y), 35, &Settings::ESP::Chams::arms);
	AddComponent (ts_chams_arms);

	ts_rainbow_chams_hands = new ToggleSwitch ("rainbow arms", LOC (ts_chams_arms->position.x + ts_chams_arms->size.x + 10, ts_chams_arms->position.y), 35, &Settings::ESP::Chams::rainbow_arms);
	AddComponent (ts_rainbow_chams_hands);

	ts_visibility_check_chams = new ToggleSwitch ("visibility check", LOC (ts_rainbow_chams_hands->position.x + ts_rainbow_chams_hands->size.x + 10, ts_rainbow_chams_hands->position.y), 35, &Settings::ESP::Chams::visibility_check);
	AddComponent (ts_visibility_check_chams);
	
	ba_crosshair = new Banner ("Crosshair", LOC (10, ts_chams_arms->position.y + ts_chams_arms->size.y + 10), size.x - 20);
	AddComponent (ba_crosshair);
	
	ts_recoil_crosshair = new ToggleSwitch ("recoil crosshair", LOC (10, ba_crosshair->position.y + ba_crosshair->size.y + 10), 35, &Settings::Recoilcrosshair::enabled);
	AddComponent (ts_recoil_crosshair);
	
	ts_fov_crosshair = new ToggleSwitch ("fov crosshair", LOC (ts_recoil_crosshair->position.x + ts_recoil_crosshair->size.x + 10, ts_recoil_crosshair->position.y), 35, &Settings::ESP::FOVCrosshair::enabled);
	AddComponent (ts_fov_crosshair);
	
	ba_other = new Banner ("Other", LOC (10, ts_fov_crosshair->position.y + ts_fov_crosshair->size.y + 10), size.x - 20);
	AddComponent (ba_other);
	
	ts_bomb = new ToggleSwitch ("bomb esp", LOC (10, ba_other->position.y + ba_other->size.y + 10), 35, &Settings::ESP::Bomb::enabled);
	AddComponent (ts_bomb);

	ts_weapons = new ToggleSwitch ("weapons esp", LOC (ts_bomb->position.x + ts_bomb->size.x + 10, ts_bomb->position.y), 35, &Settings::ESP::Weapons::enabled);
	AddComponent (ts_weapons);
	
	Hide ();
}