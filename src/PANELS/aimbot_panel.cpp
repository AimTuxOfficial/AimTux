#include "aimbot_panel.h"

AimbotPanel::AimbotPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_aimbot_enabled = new ToggleSwitchTip ("Enabled", LOC (10, 10), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::enabled, "Enables or Disables Aimbot");
	ba_aim = new Banner ("Aim", BELOW (ts_aimbot_enabled), (size.x - 20) / 2 - 5);
	ts_aimkey_only = new ToggleSwitchTip ("Aim Key Only", BELOW (ba_aim), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::aimkey_only, "Aimbot is only active when this key is pressed");
	kb_aimkey =  new KeyBind ("Aim Key", STACK (ts_aimkey_only), LOC((size.x - 20) / 6.75, 30),  &Settings::Aimbot::aimkey);
	ts_silent = new ToggleSwitchTip ("Silent Aim", BELOW (ts_aimkey_only), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::silent, "Hides aim from client view. (Spectators can see)");
	ts_rcs = new ToggleSwitchTip ("Recoil Control", BELOW (ts_silent), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::RCS::enabled, "Recoil Control. 2=perfect");
	sl_rcs = new Slider ("", STACK (ts_rcs), LOC ((size.x / 2) - ts_rcs->size.x - 30, 30), &Settings::Aimbot::RCS::value, 0.0f, 2.0f);
	ts_autoaim = new ToggleSwitchTip ("Auto Aim", BELOW (ts_rcs), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoAim::enabled, "Field of view for target to be locked onto");
	sl_fov = new Slider ("FOV", STACK (ts_autoaim), LOC ((size.x / 2) - ts_autoaim->size.x - 30, 30), &Settings::Aimbot::fov, 0.0f, 180.0f);
	ts_smooth = new ToggleSwitchTip ("Smooth", BELOW (ts_autoaim), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::Smooth::enabled, "Smoothing reduces the aimbot \"snap\". 0 for full snap. 1 for full smoothing");
	sl_smooth = new Slider ("", STACK (ts_smooth), LOC ((size.x / 2) - ts_smooth->size.x - 30, 30), &Settings::Aimbot::Smooth::value, 0.0f, Settings::Aimbot::Smooth::max);
	ts_salting = new ToggleSwitchTip ("Smooth Salting", BELOW (ts_smooth), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::Smooth::Salting::enabled, "Breaks the smoothing into smaller steps, high smooth + low salt is slightly stuttery");
	sl_salting = new Slider ("Salt Percentage", STACK (ts_salting), LOC ((size.x / 2) - ts_salting->size.x - 30, 30), &Settings::Aimbot::Smooth::Salting::percentage, 0.0f, 100.0f);
	ts_aimstep = new ToggleSwitchTip ("Aim Step", BELOW (ts_salting), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AimStep::enabled, "Adds a delay to the aimbot. Only needed for casual");
	sl_aimstep = new Slider ("", STACK (ts_aimstep), LOC ((size.x / 2) - ts_aimstep->size.x - 30, 30), &Settings::Aimbot::AimStep::value, 0.0f, 180.0f);
	sl_error = new Slider("Error Margin", BELOW(ts_aimstep), LOC((size.x / 2) - 20, 30), &Settings::Aimbot::errorMargin, 0.0f, 2.0f);
	ts_autopistol = new ToggleSwitchTip ("Auto Pistol", BELOW (sl_error), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoPistol::enabled, "Auto shoot the pistol when holding fire");
	ts_no_shoot = new ToggleSwitchTip ("No Shoot", STACK (ts_autopistol), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::no_shoot, "Don't shoot when an enemy is in the FOV - Usefull for legit settings with triggerbot");
	ts_autoshoot = new ToggleSwitchTip ("Auto Shoot", BELOW (ts_autopistol), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoShoot::enabled, "Automatically aims and shoots");
	ts_autoscope = new ToggleSwitchTip ("Auto Scope", STACK (ts_autoshoot), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoShoot::autoscope, "Automatically scopes");
	ba_target = new Banner ("Target", LOC((size.x / 2) + 5, ba_aim->position.y), ((size.x - 20) / 2) - 5);
	ts_friendly = new ToggleSwitchTip ("Friendly", BELOW (ba_target), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::friendly, "Friendly fire mode for aimbot.");
	cb_aimbone = new ComboBox<Bone>("AimBone", BELOW (ts_friendly), (size.x - 20) / 6.75, (Bone*)&Settings::Aimbot::bone, std::vector<CB_Element>
			{
					CB_Element ("HEAD", BONE_HEAD),
					CB_Element ("NECK", BONE_NECK),
					CB_Element ("UPPER SPINE", BONE_UPPER_SPINAL_COLUMN),
					CB_Element ("MIDDLE SPINE", BONE_MIDDLE_SPINAL_COLUMN),
					CB_Element ("LOWER SPINE", BONE_LOWER_SPINAL_COLUMN),
					CB_Element ("HIP", BONE_HIP),
					CB_Element ("PELVIS", BONE_PELVIS)
			}, false
	);

	AddComponent (sl_error);
	AddComponent (sl_aimstep);
	AddComponent (sl_salting);
	AddComponent (sl_smooth);
	AddComponent (sl_fov);
	AddComponent (sl_rcs);
	AddComponent (cb_aimbone);
	AddComponent (ts_friendly);
	AddComponent (ba_target);
	AddComponent (ts_autoscope);
	AddComponent (ts_autoshoot);
	AddComponent (ts_autopistol);
	AddComponent (ts_no_shoot);
	AddComponent (ts_aimstep);
	AddComponent (ts_salting);
	AddComponent (ts_smooth);
	AddComponent (ts_autoaim);
	AddComponent (ts_rcs);
	AddComponent (ts_silent);
	AddComponent (ts_silent);
	AddComponent (kb_aimkey);
	AddComponent (ts_aimkey_only);
	AddComponent (ba_aim);
	AddComponent (ts_aimbot_enabled);

	Hide ();
}
