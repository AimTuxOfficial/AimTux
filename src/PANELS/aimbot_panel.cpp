#include "aimbot_panel.h"

AimbotPanel::AimbotPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_aimbot_enabled = new ToggleSwitch ("enabled", LOC (10, 10), 33, &Settings::Aimbot::enabled);
	AddComponent (ts_aimbot_enabled);
	
	ba_aim = new Banner ("Aim", BELOW (ts_aimbot_enabled), (size.x - 20) / 2 - 5);
	AddComponent (ba_aim);

	ts_silent = new ToggleSwitch ("silent aim", BELOW (ba_aim), 33, &Settings::Aimbot::silent);
	AddComponent (ts_silent);
	
	ts_rcs = new ToggleSwitch ("recoil control", BELOW (ts_silent), 33, &Settings::Aimbot::RCS::enabled);
	AddComponent (ts_rcs);
	
	ts_autoaim = new ToggleSwitch ("auto aim", BELOW (ts_rcs), 33, &Settings::Aimbot::AutoAim::enabled);
	AddComponent (ts_autoaim);

	sl_fov = new Slider ("FOV", STACK (ts_autoaim), LOC ((size.x / 2) - ts_autoaim->size.x - 30, 33), &Settings::Aimbot::fov, 0.0f, 180.0f);
	AddComponent (sl_fov);
	
	ts_smooth = new ToggleSwitch ("smooth", BELOW (ts_autoaim), 33, &Settings::Aimbot::Smooth::enabled);
	AddComponent (ts_smooth);
	
	sl_smooth = new Slider ("", STACK (ts_smooth), LOC ((size.x / 2) - ts_smooth->size.x - 30, 33), &Settings::Aimbot::Smooth::value, 0.10f, Settings::Aimbot::Smooth::max);
	AddComponent (sl_smooth);
	
	ts_salting = new ToggleSwitch ("Smooth Salting", BELOW (ts_smooth), 33, &Settings::Aimbot::Smooth::Salting::enabled);
	AddComponent (ts_salting);
	
	sl_salting = new Slider ("Salt Percentage", STACK (ts_salting), LOC ((size.x / 2) - ts_salting->size.x - 30, 33), &Settings::Aimbot::Smooth::Salting::percentage, 0.0f, 100.0f);
	AddComponent (sl_salting);
	
	ts_aimstep = new ToggleSwitch ("aim step", BELOW (ts_salting), 33, &Settings::Aimbot::AimStep::enabled);
	AddComponent (ts_aimstep);

	sl_aimstep = new Slider ("", STACK (ts_aimstep), LOC ((size.x / 2) - ts_aimstep->size.x - 30, 33), &Settings::Aimbot::AimStep::value, 0.0f, 180.0f);
	AddComponent (sl_aimstep);

	ts_autowall = new ToggleSwitch ("auto wall", BELOW (ts_aimstep), 33, &Settings::Aimbot::AutoWall::enabled);
	AddComponent (ts_autowall);

	sl_autowall = new Slider ("min damage", STACK (ts_autowall), LOC ((size.x / 2) - ts_autowall->size.x - 30, 33), &Settings::Aimbot::AutoWall::value, 0.0f, 100.0f);
	AddComponent (sl_autowall);

	sl_error = new Slider("error margin", BELOW(ts_autowall), LOC((size.x / 2) - 20, 33), &Settings::Aimbot::errorMargin, 0.0f, 2.0f);
	AddComponent (sl_error);

	ts_autoshoot = new ToggleSwitch ("auto shoot", BELOW (sl_error), 33, &Settings::Aimbot::AutoShoot::enabled);
	AddComponent (ts_autoshoot);

	ts_autoscope = new ToggleSwitch ("auto scope", STACK (ts_autoshoot), 33, &Settings::Aimbot::AutoShoot::autoscope);
	AddComponent (ts_autoscope);
	
	ba_movement = new Banner ("Movement", BELOW (ts_autoshoot), (size.x - 20) / 2 - 5);
	AddComponent (ba_movement);
	
	ts_autocrouch = new ToggleSwitch ("auto crouch", BELOW (ba_movement), 33, &Settings::Aimbot::AutoCrouch::enabled);
	AddComponent (ts_autocrouch);

	ts_autostop = new ToggleSwitch ("auto stop", BELOW (ts_autocrouch), 33, &Settings::Aimbot::AutoStop::enabled);
	AddComponent (ts_autostop);

	ba_target = new Banner ("Target", LOC((size.x / 2) + 5, ba_aim->position.y), ((size.x - 20) / 2) - 5);
	AddComponent (ba_target);

	ts_friendly = new ToggleSwitch ("friendly", BELOW (ba_target), 33, &Settings::Aimbot::friendly);
	AddComponent (ts_friendly);

	lb_aimbone = new StackedListBox<Bone>("aimbone", BELOW (ts_friendly), ((size.x - 20) / 2) - 5, 3, (Bone*)&Settings::Aimbot::bone, std::vector<LB_Element>
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
	AddComponent (lb_aimbone);
	
	Hide ();
}

