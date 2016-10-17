#include "aimbot_window.h"

AimbotWindow* aimbot_window = nullptr;

AimbotWindow::AimbotWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_aimbot_enabled = new ToggleSwitch ("aimbot", LOC (10, 10), 33, &Settings::Aimbot::enabled);
	AddComponent (ts_aimbot_enabled);
	
	ts_silent = new ToggleSwitch ("silent aim", BELOW (ts_aimbot_enabled), 33, &Settings::Aimbot::silent);
	AddComponent (ts_silent);
	
	ba_aim = new Banner ("Aim", BELOW (ts_silent), size.x - 20);
	AddComponent (ba_aim);
	
	ts_rcs = new ToggleSwitch ("recoil control", BELOW (ba_aim), 33, &Settings::Aimbot::RCS::enabled);
	AddComponent (ts_rcs);
	
	ts_autoaim = new ToggleSwitch ("auto aim", BELOW (ts_rcs), 33, &Settings::Aimbot::AutoAim::enabled);
	AddComponent (ts_autoaim);

	sl_fov = new Slider ("FOV", STACK (ts_autoaim), LOC (size.x - ts_autoaim->size.x - 30, 33), &Settings::Aimbot::fov, 0.0f, 180.0f);
	AddComponent (sl_fov);
	
	lb_aimbone = new StackedListBox<Bones>("aimbone", BELOW (ts_autoaim), size.x - 20, 3, (Bones*)&Settings::Aimbot::bone, std::vector<LB_Element>
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
	
	ts_smooth_enable = new ToggleSwitch ("smooth", BELOW (lb_aimbone), 33, &Settings::Aimbot::Smooth::enabled);
	AddComponent (ts_smooth_enable);
	
	sl_smooth_value = new Slider ("", STACK (ts_smooth_enable), LOC (size.x - ts_smooth_enable->size.x - 30, 33), &Settings::Aimbot::Smooth::value, 0.10f, Settings::Aimbot::Smooth::max);
	AddComponent (sl_smooth_value);
	
	
	ts_aimstep = new ToggleSwitch ("aim step", BELOW (ts_smooth_enable), 33, &Settings::Aimbot::AimStep::enabled);
	AddComponent (ts_aimstep);
	
	ts_autoshoot = new ToggleSwitch ("auto shoot", BELOW (ts_aimstep), 33, &Settings::Aimbot::AutoShoot::enabled);
	AddComponent (ts_autoshoot);
	
    ts_friendly = new ToggleSwitch ("friendly", STACK (ts_aimstep), 33, &Settings::Aimbot::friendly);
    AddComponent (ts_friendly);

	ba_movement = new Banner ("Movement", BELOW (ts_autoshoot), size.x - 20);
	AddComponent (ba_movement);
	
	ts_autocrouch = new ToggleSwitch ("auto crouch", BELOW (ba_movement), 33, &Settings::Aimbot::AutoCrouch::enabled);
	AddComponent (ts_autocrouch);
	
	ts_autostop = new ToggleSwitch ("auto stop", STACK (ts_autocrouch), 33, &Settings::Aimbot::AutoStop::enabled);
	AddComponent (ts_autostop);

	
	Hide ();
}
