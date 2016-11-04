#include "visuals_panel.h"

VisualsPanel::VisualsPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_esp_enabled = new ToggleSwitch ("enabled", LOC (10, 10), 33, &Settings::ESP::enabled);
	AddComponent (ts_esp_enabled);
	
	ba_esp = new Banner ("ESP", BELOW (ts_esp_enabled), (size.x - 20) / 2 - 5);
	AddComponent (ba_esp);
	
	ts_walls = new ToggleSwitch ("walls", BELOW (ba_esp), 33, &Settings::ESP::Walls::enabled);
	AddComponent (ts_walls);

	lb_wallstype = new StackedListBox<WallBoxType>("walls type", BELOW (ts_walls), ((size.x - 20) / 2) - 5, 3, &Settings::ESP::Walls::type, std::vector<LB_Element>
			{
					LB_Element ("2D", FLAT_2D),
					LB_Element ("3D", BOX_3D),
			}
	);
	AddComponent (lb_wallstype);
	
	ts_tracer = new ToggleSwitch ("tracer", BELOW (lb_wallstype), 33, &Settings::ESP::Tracer::enabled);
	AddComponent (ts_tracer);
	
	ts_name = new ToggleSwitch ("show name", BELOW (ts_tracer), 33, &Settings::ESP::Info::showName);
	AddComponent (ts_name);
	
	ts_health = new ToggleSwitch ("show health", BELOW (ts_name), 33, &Settings::ESP::Info::showHealth);
	AddComponent (ts_health);
	
	ts_bones = new ToggleSwitch ("show bones", BELOW (ts_health), 33, &Settings::ESP::Bones::enabled);
	AddComponent (ts_bones);
	
	ts_visibility_check = new ToggleSwitch ("visibility check", BELOW (ts_bones), 33, &Settings::ESP::visibility_check);
	AddComponent (ts_visibility_check);

	ba_crosshair = new Banner ("Crosshair", BELOW (ts_visibility_check), (size.x - 20) / 2 - 5);
	AddComponent (ba_crosshair);
	
	ts_recoil_crosshair = new ToggleSwitch ("recoil crosshair", BELOW (ba_crosshair), 33, &Settings::Recoilcrosshair::enabled);
	AddComponent (ts_recoil_crosshair);
	
	ts_fov_crosshair = new ToggleSwitch ("fov crosshair", BELOW (ts_recoil_crosshair), 33, &Settings::ESP::FOVCrosshair::enabled);
	AddComponent (ts_fov_crosshair);

	ba_chams = new Banner ("Chams", LOC((size.x / 2) + 5, ba_esp->position.y), ((size.x - 20) / 2) - 5);
	AddComponent (ba_chams);

	ts_chams_players = new ToggleSwitch ("players", BELOW (ba_chams), 33, &Settings::ESP::Chams::players);
	AddComponent (ts_chams_players);

	ts_chams_arms = new ToggleSwitch ("arms", BELOW (ts_chams_players), 33, &Settings::ESP::Chams::arms);
	AddComponent (ts_chams_arms);

	ts_chams_rainbow_arms = new ToggleSwitch ("rainbow arms", STACK (ts_chams_arms), 33, &Settings::ESP::Chams::rainbow_arms);
	AddComponent (ts_chams_rainbow_arms);

	ts_chams_wireframe_arms = new ToggleSwitch ("wireframe arms", BELOW (ts_chams_arms), 33, &Settings::ESP::Chams::wireframe_arms);
	AddComponent (ts_chams_wireframe_arms);

	ts_chams_no_arms = new ToggleSwitch ("no arms", BELOW (ts_chams_wireframe_arms), 33, &Settings::ESP::Chams::no_arms);
	AddComponent (ts_chams_no_arms);

	ts_chams_visibility_check = new ToggleSwitch ("visibility check", BELOW (ts_chams_no_arms), 33, &Settings::ESP::Chams::visibility_check);
	AddComponent (ts_chams_visibility_check);

	lb_chamstype = new StackedListBox<ChamsType>("chams type", BELOW (ts_chams_visibility_check), ((size.x - 20) / 2) - 5, 3, &Settings::ESP::Chams::type, std::vector<LB_Element>
			{
					LB_Element ("NORMAL", CHAMS),
					LB_Element ("FLAT", CHAMS_FLAT),
			}
	);
	AddComponent (lb_chamstype);

	ba_other = new Banner ("Other", BELOW (lb_chamstype), ((size.x - 20) / 2) - 5);
	AddComponent (ba_other);

	ts_bomb = new ToggleSwitch ("bomb esp", BELOW (ba_other), 33, &Settings::ESP::Bomb::enabled);
	AddComponent (ts_bomb);

	ts_weapons = new ToggleSwitch ("weapons esp", BELOW (ts_bomb), 33, &Settings::ESP::Weapons::enabled);
	AddComponent (ts_weapons);

	ts_glow = new ToggleSwitch ("glow", BELOW (ts_weapons), 33, &Settings::ESP::Glow::enabled);
	AddComponent (ts_glow);

	ts_dlights = new ToggleSwitch ("dlights", BELOW (ts_glow), 33, &Settings::Dlights::enabled);
	AddComponent (ts_dlights);

	sl_dlights = new Slider ("radius", STACK (ts_dlights), LOC ((size.x / 2) - ts_dlights->size.x - 30, 33), &Settings::Dlights::radius, 0.0f, 1000.0f);
	AddComponent (sl_dlights);
	
	ts_view_norecoil = new ToggleSwitch ("no visual recoil", BELOW (ts_dlights), 33, &Settings::View::NoPunch::enabled);
	AddComponent (ts_view_norecoil);
	
	Hide ();
}