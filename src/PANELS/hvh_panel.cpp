#include "hvh_panel.h"

HVHPanel::HVHPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ba_antiaim = new Banner ("Anti Aim", LOC (10, 10), (size.x - 20) / 2 - 5);
	AddComponent (ba_antiaim);

	ts_antiaim_y = new ToggleSwitch ("Y Axis", BELOW (ba_antiaim), LOC((size.x - 20) / 6.75, 30), &Settings::AntiAim::enabled_Y);
	AddComponent (ts_antiaim_y);

	lb_antiaim_y = new ListBox<AntiAimType_Y> ("anti aim type", BELOW (ts_antiaim_y), (size.x - 20) / 6.75, &Settings::AntiAim::type_Y, std::vector<LB_Element>
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

	ts_antiaim_x = new ToggleSwitch ("X Axis", STACK(ts_antiaim_y), LOC((size.x - 20) / 6.75, 30), &Settings::AntiAim::enabled_X);
	AddComponent (ts_antiaim_x);

	lb_antiaim_x = new ListBox<AntiAimType_X> ("anti aim type", BELOW (ts_antiaim_x), (size.x - 20) / 6.75, &Settings::AntiAim::type_X, std::vector<LB_Element>
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

	ba_movement = new Banner ("Movement", BELOW (lb_antiaim_y), (size.x - 20) / 2 - 5);
	AddComponent (ba_movement);

	ts_autocrouch = new ToggleSwitch ("Auto Crouch", BELOW (ba_movement), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoCrouch::enabled);
	AddComponent (ts_autocrouch);

	ts_autostop = new ToggleSwitch ("Auto Stop", STACK (ts_autocrouch), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoStop::enabled);
	AddComponent (ts_autostop);

	ba_autowall = new Banner ("Auto Wall", STACK (ba_antiaim), (size.x - 20) / 2 - 5);
	AddComponent (ba_autowall);

	ts_autowall = new ToggleSwitch ("Enabled", BELOW (ba_autowall), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoWall::enabled);
	AddComponent (ts_autowall);

	sl_autowall = new Slider ("min damage", BELOW (ts_autowall), LOC (ba_autowall->size.x, 30), &Settings::Aimbot::AutoWall::value, 0.0f, 100.0f);
	AddComponent (sl_autowall);

	lb_bone_select_multi = new MS_ListBox<Hitbox> ("Autowall bones", BELOW (sl_autowall), (size.x - 20) / 6.75, &Settings::Aimbot::AutoWall::bones, std::vector<LB_Element>
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
