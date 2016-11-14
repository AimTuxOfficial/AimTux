#include "visuals_panel.h"

VisualsPanel::VisualsPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_esp_enabled = new ToggleSwitchTip ("Enabled", LOC (10, 10), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::enabled, "Whether visual based cheats are enabled");
	ba_esp = new Banner ("ESP", BELOW (ts_esp_enabled), (size.x - 20) / 2 - 5);
	ts_walls = new ToggleSwitchTip ("Walls", BELOW (ba_esp), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Walls::enabled, "Show boxes around players");
	ts_tracer = new ToggleSwitchTip ("Tracers", BELOW (ts_walls), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Tracer::enabled, "Show a line from your position to the enemies position");
	ts_name = new ToggleSwitchTip ("Show Name", BELOW (ts_tracer), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Info::showName, "Show a players name");
	ts_health = new ToggleSwitchTip ("Show Health", BELOW (ts_name), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Info::showHealth, "Show a players health");
	ts_weapon = new ToggleSwitchTip ("Show Weapon", BELOW (ts_health), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Info::showWeapon, "Show what a player is holding");
	ts_color_code = new ToggleSwitchTip ("Color Code", BELOW (ts_weapon), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Info::colorCode, "Color code text based on team");
	ts_bones = new ToggleSwitchTip ("Show Bones", BELOW (ts_color_code), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Bones::enabled, "Show player bones");
	ts_friendly = new ToggleSwitchTip ("Show Friendly", BELOW (ts_bones), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::friendly, "Show friendlies");
	ts_visibility_check = new ToggleSwitchTip ("Visibility Check", BELOW (ts_friendly), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::visibility_check, "Only draw ESP elements when an enemy is visible");
	ba_crosshair = new Banner ("Crosshair", BELOW (ts_visibility_check), (size.x - 20) / 2 - 5);
	ts_recoil_crosshair = new ToggleSwitchTip ("Recoil Crosshair", BELOW (ba_crosshair), LOC((size.x - 20) / 6.75, 30), &Settings::Recoilcrosshair::enabled, "Show a weapon recoil pattern as a crosshair");
	ts_fov_crosshair = new ToggleSwitchTip ("FOV Circle", BELOW (ts_recoil_crosshair), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::FOVCrosshair::enabled, "Area of auto aim");
	ba_chams = new Banner ("Chams", LOC((size.x / 2) + 5, ba_esp->position.y), ((size.x - 20) / 2) - 5);
	ts_chams_players = new ToggleSwitchTip ("Players", BELOW (ba_chams), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Chams::players, "Show players in chams");
	ts_chams_arms = new ToggleSwitchTip ("Arms", BELOW (ts_chams_players), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Chams::Arms::enabled, "Change your arm viewmodel");
	ts_chams_visibility_check = new ToggleSwitchTip ("Visibility Check", BELOW (ts_chams_arms), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Chams::visibility_check, "Only show player chams when visible");
	ba_other = new Banner ("Other", BELOW (ts_chams_visibility_check), ((size.x - 20) / 2) - 5);
	ts_bomb = new ToggleSwitchTip ("Bomb ESP", BELOW (ba_other), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Bomb::enabled, "Show ESP box around bomb along with countdown");
	ts_weapons = new ToggleSwitchTip ("Weapon Names", BELOW (ts_bomb), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Weapons::enabled, "Show dropped weapon names");
	ts_glow = new ToggleSwitchTip ("Glow", BELOW (ts_weapons), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Glow::enabled, "Show a glow around weapons and people");
	ts_dlights = new ToggleSwitchTip ("Dlights", BELOW (ts_glow), LOC((size.x - 20) / 6.75, 30), &Settings::Dlights::enabled, "Show a light source around players");
	sl_dlights = new Slider ("Radius", STACK (ts_dlights), LOC ((size.x / 2) - ts_dlights->size.x - 30, 30), &Settings::Dlights::radius, 0.0f, 1000.0f);
	ts_view_norecoil = new ToggleSwitchTip ("No View Punch", BELOW (ts_dlights), LOC((size.x - 20) / 6.75, 30), &Settings::View::NoPunch::enabled, "Disables the visual punch when shooting or being shot");
#ifdef EXPERIMENTAL_SETTINGS
	ts_show_scope_border = new ToggleSwitchTip ("Show Scope Border", BELOW (ts_view_norecoil), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::show_scope_border, "Disables the scope border. (Bit buggy)");
#endif
	cb_armstype = new ComboBox<ArmsType>("arms type", STACK (ts_chams_arms), (size.x - 20) / 6.75, &Settings::ESP::Chams::Arms::type, std::vector<CB_Element>
			{
					CB_Element ("Rainbow", RAINBOW),
					CB_Element ("Wire Frame", WIREFRAME),
					CB_Element ("None", NONE),
					CB_Element ("Default", DEFAULT)
			}, false
	);
	cb_chamstype = new ComboBox<ChamsType>("chams type", STACK (ts_chams_players), (size.x - 20) / 6.75, &Settings::ESP::Chams::type, std::vector<CB_Element>
			{
					CB_Element ("NORMAL", CHAMS),
					CB_Element ("FLAT", CHAMS_FLAT),
			}, false
	);
	cb_wallstype = new ComboBox<WallBoxType>("walls type", STACK (ts_walls), (size.x - 20) / 6.75, &Settings::ESP::Walls::type, std::vector<CB_Element>
			{
					CB_Element ("2D", FLAT_2D),
					CB_Element ("3D", BOX_3D),
			}, false
	);


#ifdef EXPERIMENTAL_SETTINGS
	AddComponent (ts_show_scope_border);
#endif
	AddComponent (ts_view_norecoil);
	AddComponent (sl_dlights);
	AddComponent (ts_dlights);
	AddComponent (ts_glow);
	AddComponent (ts_weapons);
	AddComponent (ts_bomb);
	AddComponent (ba_other);
	AddComponent (ba_other);
	AddComponent (ts_chams_visibility_check);
	AddComponent (ba_chams);
	AddComponent (ts_fov_crosshair);
	AddComponent (ts_recoil_crosshair);
	AddComponent (ba_crosshair);
	AddComponent (ts_visibility_check);
	AddComponent (ts_friendly);
	AddComponent (ts_bones);
	AddComponent (ts_color_code);
	AddComponent (ts_weapon);
	AddComponent (ts_health);
	AddComponent (ts_name);
	AddComponent (ts_tracer);
	AddComponent (ba_esp);
	AddComponent (ts_esp_enabled);
	AddComponent (cb_armstype);
	AddComponent (cb_chamstype);
	AddComponent(cb_wallstype);
	AddComponent (ts_walls);
	AddComponent (ts_chams_arms);
	AddComponent (ts_chams_players);

	Hide ();
}
