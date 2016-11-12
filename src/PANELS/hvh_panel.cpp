#include "hvh_panel.h"

HVHPanel::HVHPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ba_antiaim = new Banner ("Antiaim", LOC (10, 10), (size.x - 20) / 2 - (5) - 60);
	AddComponent (ba_antiaim);

	ts_antiaim_y = new ToggleSwitch ("y axis", BELOW (ba_antiaim), 33, &Settings::AntiAim::enabled_Y);
	AddComponent (ts_antiaim_y);
	
	lb_antiaim_y = new ListBox<AntiAimType_Y> ("anti aim type", BELOW (ts_antiaim_y), 200, &Settings::AntiAim::type_Y, std::vector<LB_Element>
		{
			LB_Element ("SLOW SPIN", SPIN_SLOW),
			LB_Element ("FAST SPIN", SPIN_FAST),
			LB_Element ("JITTER", JITTER),
			LB_Element ("SIDE", SIDE),
			LB_Element ("BACKWARDS", BACKWARDS),
			LB_Element ("FAKE4", FAKE4),
			LB_Element ("FAKE BACKWARDS", BACKWARDS_FAKE),
			LB_Element ("FAKE SIDE FLIP", SIDE_FLIP_FAKE),
			LB_Element ("FAKE SIDE L", SIDE_FAKE_LEFT),
			LB_Element ("FAKE SIDE R", SIDE_FAKE_RIGHT)
		}
	);
	AddComponent (lb_antiaim_y);

	ts_antiaim_x = new ToggleSwitch ("x axis", LOC (lb_antiaim_y->position.x + lb_antiaim_y->size.x + 10, lb_antiaim_y->position.y - 45), 33, &Settings::AntiAim::enabled_X);
	AddComponent (ts_antiaim_x);

	lb_antiaim_x = new ListBox<AntiAimType_X> ("anti aim type", BELOW (ts_antiaim_x), 200, &Settings::AntiAim::type_X, std::vector<LB_Element>
		{
			LB_Element ("UP", STATIC_UP),
			LB_Element ("DOWN", STATIC_DOWN),
#ifdef UNTRUSTED_SETTINGS
			LB_Element ("FAKE UP", STATIC_UP_FAKE),
			LB_Element ("FAKE DOWN", STATIC_DOWN_FAKE),
#endif
		}
	);
	AddComponent (lb_antiaim_x);
	
	ba_autowall = new Banner ("Autowall", STACK (ba_antiaim), (size.x - 20) / 2 - (5) + 60);
	AddComponent (ba_autowall);
	
	ts_autowall = new ToggleSwitch ("auto wall", BELOW (ba_autowall), 33, &Settings::Aimbot::AutoWall::enabled);
	AddComponent (ts_autowall);

	sl_autowall = new Slider ("min damage", BELOW (ts_autowall), LOC (ba_autowall->size.x, 33), &Settings::Aimbot::AutoWall::value, 0.0f, 100.0f);
	AddComponent (sl_autowall);

	lb_bone_select_multi = new MS_ListBox<Hitbox> ("Autowall bones", BELOW (sl_autowall), 170, &Settings::Aimbot::AutoWall::bones, std::vector<LB_Element>
		{
			LB_Element ("HEAD", HITBOX_HEAD),
			LB_Element ("NECK", HITBOX_NECK),
			LB_Element ("PELVIS", HITBOX_PELVIS),
			LB_Element ("SPINE", HITBOX_SPINE),
			LB_Element ("LEGS", HITBOX_LEGS),
			LB_Element ("ARMS", HITBOX_ARMS)
		}
	);
	AddComponent (lb_bone_select_multi);
	
	Hide ();
}
