#include "hvh_panel.h"

bool switchAA = false;

HVHPanel::HVHPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ba_antiaim = new Banner ("Anti Aim", LOC (10, 10), (size.x - 20) / 2 - 5);
	ts_antiaim_y = new ToggleSwitchTip ("Y Axis", BELOW (ba_antiaim), LOC((size.x - 20) / 6.75, 30), &Settings::AntiAim::enabled_Y, "Anti-Aim Y Axis");
	cb_antiaim_y = new ComboBox<AntiAimType_Y> ("Norm AA Type", STACK (ts_antiaim_y), (size.x - 20) / 5, &Settings::AntiAim::type_Y, std::vector<CB_Element>
		{
			CB_Element ("SLOW SPIN", SPIN_SLOW),
			CB_Element ("FAST SPIN", SPIN_FAST),
			CB_Element ("JITTER", JITTER),
			CB_Element ("SIDE", SIDE),
			CB_Element ("BACKWARDS", BACKWARDS)
		}, false
	);
	cb_fake_antiaim_y = new ComboBox<AntiAimType_Y> ("Fake AA Type", STACK (ts_antiaim_y), (size.x - 20) / 5, &Settings::AntiAim::type_Y, std::vector<CB_Element>
		{
			CB_Element ("FAKE BACKWARDS JITTER", FAKE_BACKWARDS_JITTER),
			CB_Element ("FAKE STATIC", STATIC_FAKE),
			CB_Element ("FAKE STATIC FOLLOW", STATIC_FAKE_FOLLOW),
			CB_Element ("FAKE SLOW SPIN", SPIN_SLOW_FAKE),
			CB_Element ("FAKE FAST SPIN", SPIN_FAST_FAKE),
			CB_Element ("FAKE FORWARDS", FORWARDS_FAKE),
			CB_Element ("FAKE BACKWARDS", BACKWARDS_FAKE),
			CB_Element ("FAKE SIDE FLIP", SIDE_FLIP_FAKE),
			CB_Element ("FAKE SIDE L", SIDE_FAKE_LEFT),
			CB_Element ("FAKE SIDE R", SIDE_FAKE_RIGHT)
		}, false
	);
	ts_antiaim_x = new ToggleSwitchTip ("X Axis", BELOW(ts_antiaim_y), LOC((size.x - 20) / 6.75, 30), &Settings::AntiAim::enabled_X, "Anti-Aim X Axis");
	cb_antiaim_x = new ComboBox<AntiAimType_X> ("anti aim type", STACK (ts_antiaim_x), (size.x - 20) / 5, &Settings::AntiAim::type_X, std::vector<CB_Element>
		{
			CB_Element ("UP", STATIC_UP),
			CB_Element ("DOWN", STATIC_DOWN),
			CB_Element ("FRONT", STATIC_FRONT),
			CB_Element ("DANCE", DANCE),
#ifdef UNTRUSTED_SETTINGS
			CB_Element ("FAKE UP", STATIC_UP_FAKE),
			CB_Element ("FAKE DOWN", STATIC_DOWN_FAKE),
#endif
		}, false
	);
	ts_edge_hide = new ToggleSwitchTip ("Edge", BELOW (ts_antiaim_x), LOC ((size.x - 20) / 6.75, 30), &Settings::AntiAim::HeadEdge::enabled, "Hides the head in the closest wall");
	sl_edge_distance = new Slider ("min distance", STACK (ts_edge_hide), LOC (ba_antiaim->size.x - (10) - ts_edge_hide->size.x, 30), &Settings::AntiAim::HeadEdge::distance, 10.0f, 30.0f);
	ba_movement = new Banner ("Movement", BELOW (ts_edge_hide), (size.x - 20) / 2 - 5);
	ts_autocrouch = new ToggleSwitchTip ("Auto Crouch", BELOW (ba_movement), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoCrouch::enabled, "Auto crouch when an enemy is targetable");
	ts_autostop = new ToggleSwitchTip ("Auto Stop", STACK (ts_autocrouch), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoStop::enabled, "Auto stop when an enemy is targetable");
	ba_resolver = new Banner ("Resolver", BELOW (ts_autocrouch), (size.x - 20) / 2 - 5);
	ts_resolver = new ToggleSwitchTip ("Resolver", BELOW (ba_resolver), LOC((size.x - 20) / 6.75, 30), &Settings::Resolver::enabled, "Resolves fake angles");
	ba_autowall = new Banner ("Auto Wall", STACK (ba_antiaim), (size.x - 20) / 2 - 5);
	ts_autowall = new ToggleSwitchTip ("Enabled", BELOW (ba_autowall), LOC((size.x - 20) / 6.75, 30), &Settings::Aimbot::AutoWall::enabled, "Automatically shoots an enemy when possible");
	sl_autowall = new Slider ("min damage", BELOW (ts_autowall), LOC (ba_autowall->size.x, 30), &Settings::Aimbot::AutoWall::value, 0.0f, 100.0f);
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
	bn_switchAA = new OutlinedButton("Toggle Fake Y AA", STACK(cb_antiaim_y), LOC((size.x - 20) / 7.75 + 4, 30));
	bn_switchAA->OnClickedEvent = MFUNC (&HVHPanel::bn_switchAA_clicked, this);

	AddComponent(bn_switchAA);

	AddComponent (cb_antiaim_x);

	AddComponent (cb_antiaim_y);

	AddComponent (ts_edge_hide);
	AddComponent (sl_edge_distance);
	AddComponent (lb_bone_select_multi);
	AddComponent (sl_autowall);
	AddComponent (ts_autowall);
	AddComponent (ba_autowall);
	AddComponent (ts_autostop);
	AddComponent (ts_autocrouch);
	AddComponent (ba_movement);
	AddComponent (ba_resolver);
	AddComponent (ts_resolver);
	AddComponent (ts_antiaim_x);
	AddComponent (ts_antiaim_y);
	AddComponent (ba_antiaim);

	Hide ();
}

void HVHPanel::bn_switchAA_clicked()
{
	cvar->ConsoleColorPrintf(ColorRGBA(255, 100, 100), "%d\n", &Settings::AntiAim::type_X);
	switchAA = !switchAA;
	if(!switchAA){
		RemoveComponent(cb_fake_antiaim_y);
		AddComponent (cb_antiaim_y);
		bn_switchAA->text = "Toggle Fake Y AA";
	}else if (switchAA){
		RemoveComponent (cb_antiaim_y);
		AddComponent(cb_fake_antiaim_y);
		bn_switchAA->text = "Toggle Normal Y AA";
	}

}
