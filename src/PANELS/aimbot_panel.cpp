#include "aimbot_panel.h"

AimbotPanel::AimbotPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_aimbot_enabled = new ToggleSwitch ("Enabled", LOC (10, 10), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.enabled);
	AddComponent (ts_aimbot_enabled);

	ba_aim = new Banner ("Aim", BELOW (ts_aimbot_enabled), (size.x - 20) / 2 - 5);
	AddComponent (ba_aim);

	ts_aimkey_only = new ToggleSwitch ("Aim Key Only", BELOW (ba_aim), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.aimkey_only);
	AddComponent (ts_aimkey_only);

	kb_aimkey =  new KeyBind ("Aim Key", STACK (ts_aimkey_only), LOC((size.x - 20) / 6.75, 30),  &cSettings.Aimbot.aimkey);
	AddComponent(kb_aimkey);

	ts_silent = new ToggleSwitch ("Silent Aim", BELOW (ts_aimkey_only), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.silent);
	AddComponent (ts_silent);

	ts_rcs = new ToggleSwitch ("Recoil Control", BELOW (ts_silent), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.RCS.enabled);
	AddComponent (ts_rcs);

	sl_rcs = new Slider ("", STACK (ts_rcs), LOC ((size.x / 2) - ts_rcs->size.x - 30, 30), &cSettings.Aimbot.RCS.value, 0.0f, 2.0f);
	AddComponent (sl_rcs);

	ts_autoaim = new ToggleSwitch ("Auto Aim", BELOW (ts_rcs), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.AutoAim.enabled);
	AddComponent (ts_autoaim);

	sl_fov = new Slider ("FOV", STACK (ts_autoaim), LOC ((size.x / 2) - ts_autoaim->size.x - 30, 30), &cSettings.Aimbot.fov, 0.0f, 180.0f);
	AddComponent (sl_fov);

	ts_smooth = new ToggleSwitch ("Smooth", BELOW (ts_autoaim), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.Smooth.enabled);
	AddComponent (ts_smooth);

	sl_smooth = new Slider ("", STACK (ts_smooth), LOC ((size.x / 2) - ts_smooth->size.x - 30, 30), &cSettings.Aimbot.Smooth.value, 0.10f, cSettings.Aimbot.Smooth.max);
	AddComponent (sl_smooth);

	ts_salting = new ToggleSwitch ("Smooth Salting", BELOW (ts_smooth), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.Smooth.Salting.enabled);
	AddComponent (ts_salting);

	sl_salting = new Slider ("Salt Percentage", STACK (ts_salting), LOC ((size.x / 2) - ts_salting->size.x - 30, 30), &cSettings.Aimbot.Smooth.Salting.percentage, 0.0f, 100.0f);
	AddComponent (sl_salting);

	ts_aimstep = new ToggleSwitch ("Aim Step", BELOW (ts_salting), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.AimStep.enabled);
	AddComponent (ts_aimstep);

	sl_aimstep = new Slider ("", STACK (ts_aimstep), LOC ((size.x / 2) - ts_aimstep->size.x - 30, 30), &cSettings.Aimbot.AimStep.value, 0.0f, 180.0f);
	AddComponent (sl_aimstep);

	sl_error = new Slider("Error Margin", BELOW(ts_aimstep), LOC((size.x / 2) - 20, 30), &cSettings.Aimbot.errorMargin, 0.0f, 2.0f);
	AddComponent (sl_error);

	ts_autopistol = new ToggleSwitch ("Auto Pistol", BELOW (sl_error), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.AutoPistol.enabled);
	AddComponent (ts_autopistol);

	ts_autoshoot = new ToggleSwitch ("Auto Shoot", BELOW (ts_autopistol), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.AutoShoot.enabled);
	AddComponent (ts_autoshoot);

	ts_autoscope = new ToggleSwitch ("Auto Scope", STACK (ts_autoshoot), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.AutoShoot.autoscope);
	AddComponent (ts_autoscope);

	ba_target = new Banner ("Target", LOC((size.x / 2) + 5, ba_aim->position.y), ((size.x - 20) / 2) - 5);
	AddComponent (ba_target);

	ts_friendly = new ToggleSwitch ("Friendly", BELOW (ba_target), LOC((size.x - 20) / 6.75, 30), &cSettings.Aimbot.friendly);
	AddComponent (ts_friendly);

	lb_aimbone = new StackedListBox<Bone>("AimBone", BELOW (ts_friendly), ((size.x - 20) / 2) - 5, 3, (Bone*)&cSettings.Aimbot.bone, std::vector<LB_Element>
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
