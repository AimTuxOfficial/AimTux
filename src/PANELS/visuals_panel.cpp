#include "visuals_panel.h"

VisualsPanel::VisualsPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_esp_enabled = new ToggleSwitch ("Enabled", LOC (10, 10), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::enabled);
	AddComponent (ts_esp_enabled);

	ba_esp = new Banner ("ESP", BELOW (ts_esp_enabled), (size.x - 20) / 2 - 5);
	AddComponent (ba_esp);

	ts_walls = new ToggleSwitch ("Walls", BELOW (ba_esp), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Walls::enabled);
	AddComponent (ts_walls);

	lb_wallstype = new StackedListBox<WallBoxType>("walls type", BELOW (ts_walls), ((size.x - 20) / 2) - 5, 3, &Settings::ESP::Walls::type, std::vector<LB_Element>
			{
					LB_Element ("2D", FLAT_2D),
					LB_Element ("3D", BOX_3D),
			}
	);
	AddComponent (lb_wallstype);

	ts_tracer = new ToggleSwitch ("Tracers", BELOW (lb_wallstype), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Tracer::enabled);
	AddComponent (ts_tracer);

	ts_name = new ToggleSwitch ("Show Name", BELOW (ts_tracer), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Info::showName);
	AddComponent (ts_name);

	ts_health = new ToggleSwitch ("Show Health", BELOW (ts_name), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Info::showHealth);
	AddComponent (ts_health);

	ts_bones = new ToggleSwitch ("Show Bones", BELOW (ts_health), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Bones::enabled);
	AddComponent (ts_bones);

	ts_friendly = new ToggleSwitch ("Show Friendly", BELOW (ts_bones), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::friendly);
	AddComponent (ts_friendly);

	ts_visibility_check = new ToggleSwitch ("Visibility Check", BELOW (ts_friendly), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::visibility_check);
	AddComponent (ts_visibility_check);

	ba_crosshair = new Banner ("Crosshair", BELOW (ts_visibility_check), (size.x - 20) / 2 - 5);
	AddComponent (ba_crosshair);

	ts_recoil_crosshair = new ToggleSwitch ("Recoil Crosshair", BELOW (ba_crosshair), LOC((size.x - 20) / 6.75, 30), &Settings::Recoilcrosshair::enabled);
	AddComponent (ts_recoil_crosshair);

	ts_fov_crosshair = new ToggleSwitch ("FOV Circle", BELOW (ts_recoil_crosshair), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::FOVCrosshair::enabled);
	AddComponent (ts_fov_crosshair);

	ba_chams = new Banner ("Chams", LOC((size.x / 2) + 5, ba_esp->position.y), ((size.x - 20) / 2) - 5);
	AddComponent (ba_chams);

	ts_chams_players = new ToggleSwitch ("Players", BELOW (ba_chams), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Chams::players);
	AddComponent (ts_chams_players);

	lb_chamstype = new StackedListBox<ChamsType>("chams type", BELOW (ts_chams_players), ((size.x - 20) / 2) - 5, 3, &Settings::ESP::Chams::type, std::vector<LB_Element>
			{
					LB_Element ("NORMAL", CHAMS),
					LB_Element ("FLAT", CHAMS_FLAT),
			}
	);
	AddComponent (lb_chamstype);

	ts_chams_arms = new ToggleSwitch ("Arms", BELOW (lb_chamstype), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Chams::Arms::enabled);
	AddComponent (ts_chams_arms);

	lb_armstype = new StackedListBox<ArmsType>("arms type", BELOW (ts_chams_arms), ((size.x - 20) / 2) - 5, 3, &Settings::ESP::Chams::Arms::type, std::vector<LB_Element>
			{
					LB_Element ("Rainbow", RAINBOW),
					LB_Element ("Wire Frame", WIREFRAME),
					LB_Element ("None", NONE),
					LB_Element ("Default", DEFAULT)
			}
	);
	AddComponent (lb_armstype);

	ts_chams_visibility_check = new ToggleSwitch ("Visibility Check", BELOW (lb_armstype), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Chams::visibility_check);
	AddComponent (ts_chams_visibility_check);

	ba_other = new Banner ("Other", BELOW (ts_chams_visibility_check), ((size.x - 20) / 2) - 5);
	AddComponent (ba_other);

	ts_bomb = new ToggleSwitch ("Bomb ESP", BELOW (ba_other), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Bomb::enabled);
	AddComponent (ts_bomb);

	ts_weapons = new ToggleSwitch ("Weapon Names", BELOW (ts_bomb), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Weapons::enabled);
	AddComponent (ts_weapons);

	ts_glow = new ToggleSwitch ("Weapon Glow", BELOW (ts_weapons), LOC((size.x - 20) / 6.75, 30), &Settings::ESP::Glow::enabled);
	AddComponent (ts_glow);

	ts_dlights = new ToggleSwitch ("Dlights", BELOW (ts_glow), LOC((size.x - 20) / 6.75, 30), &Settings::Dlights::enabled);
	AddComponent (ts_dlights);

	sl_dlights = new Slider ("Radius", STACK (ts_dlights), LOC ((size.x / 2) - ts_dlights->size.x - 30, 30), &Settings::Dlights::radius, 0.0f, 1000.0f);
	AddComponent (sl_dlights);

	ts_view_norecoil = new ToggleSwitch ("No View Punch", BELOW (ts_dlights), LOC((size.x - 20) / 6.75, 30), &Settings::View::NoPunch::enabled);
	AddComponent (ts_view_norecoil);

	Hide ();
}
