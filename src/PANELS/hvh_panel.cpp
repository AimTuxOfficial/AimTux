#include "hvh_panel.h"

HVHPanel::HVHPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_antiaim_x = new ToggleSwitch ("x axis", LOC (10, 10), 33, &Settings::AntiAim::enabled_X);
	AddComponent (ts_antiaim_x);
	
	
	lb_antiaim_x = new ListBox<AntiAimType_X> ("anti aim type", LOC (10, ts_antiaim_x->position.y + ts_antiaim_x->size.y + 10), 170, &Settings::AntiAim::type_X, std::vector<LB_Element>
		{
			LB_Element ("UP", STATIC_UP),
			LB_Element ("DOWN", STATIC_DOWN)
		}
	);
	AddComponent (lb_antiaim_x);
	
	
	
	lb_antiaim_y = new ListBox<AntiAimType_Y> ("anti aim type", LOC (lb_antiaim_x->position.x + lb_antiaim_x->size.x + 10, lb_antiaim_x->position.y), 170, &Settings::AntiAim::type_Y, std::vector<LB_Element>
		{
			LB_Element ("SLOW SPIN", SPIN_SLOW),
			LB_Element ("FAST SPIN", SPIN_FAST),
			LB_Element ("JITTER", JITTER),
			LB_Element ("SIDE", SIDE),
			LB_Element ("BACKWARDS", BACKWARDS)
		}
	);
	AddComponent (lb_antiaim_y);
	
	ts_antiaim_y = new ToggleSwitch ("y axis", LOC (lb_antiaim_x->position.x + lb_antiaim_x->size.x + 10, lb_antiaim_y->position.y - 45), 33, &Settings::AntiAim::enabled_Y);
	AddComponent (ts_antiaim_y);
	
	
	lb_bone_select_multi = new MS_ListBox<Bone> ("Autowall Bone", LOC (lb_antiaim_y->position.x + lb_antiaim_y->size.x + 10, lb_antiaim_y->position.y), 170, &Settings::Aimbot::AutoWall::Bone, std::vector<LB_Element>
		{
			LB_Element ("HEAD", BONE_HEAD),
			LB_Element ("NECK", BONE_NECK),
			LB_Element ("UPPER SPINE", BONE_UPPER_SPINAL_COLUMN),
			LB_Element ("MIDDLE SPINE", BONE_MIDDLE_SPINAL_COLUMN),
			LB_Element ("LOWER SPINE", BONE_LOWER_SPINAL_COLUMN),
			LB_Element ("HIP", BONE_HIP),
			LB_Element ("PELVIS", BONE_PELVIS)
		}
	);
	AddComponent (lb_bone_select_multi);
	
	Hide ();
}
