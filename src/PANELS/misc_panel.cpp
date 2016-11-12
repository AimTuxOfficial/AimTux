#include "misc_panel.h"

MiscPanel::MiscPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ba_movement = new Banner ("Movement", LOC (10, 10), (size.x - 20) / 2 - 5);
	AddComponent (ba_movement);

	ts_bhop = new ToggleSwitch ("Bunny Hop", BELOW (ba_movement), LOC((size.x - 20) / 6.75, 30), &Settings::BHop::enabled);
	AddComponent (ts_bhop);

	ts_autostrafe = new ToggleSwitch ("Auto Strafe", STACK (ts_bhop), LOC((size.x - 20) / 6.75, 30), &Settings::AutoStrafe::enabled);
	AddComponent (ts_autostrafe);

	ts_airstuck = new ToggleSwitch ("Air Stuck", BELOW (ts_bhop), LOC((size.x - 20) / 6.75, 30), &Settings::Airstuck::enabled);
	AddComponent (ts_airstuck);

	kb_airstuck_key =  new KeyBind ("", STACK (ts_airstuck), LOC((size.x - 20) / 6.75, 30),  &Settings::Airstuck::key);
	AddComponent(kb_airstuck_key);

#ifdef UNTRUSTED_SETTINGS
	ts_teleport = new ToggleSwitch ("Teleport", BELOW (ts_airstuck), LOC((size.x - 20) / 6.75, 30), &Settings::Teleport::enabled);
	AddComponent (ts_teleport);

	kb_teleport_key =  new KeyBind ("", STACK (ts_teleport), LOC((size.x - 20) / 6.75, 30),  &Settings::Teleport::key);
	AddComponent(kb_teleport_key);

	ba_spammer = new Banner ("Spammer", BELOW (ts_teleport), (size.x - 20) / 2 - 5);
#else
	ba_spammer = new Banner ("Spammer", BELOW (ts_airstuck), (size.x - 20) / 2 - 5);
#endif
	AddComponent (ba_spammer);

	ts_position_spammer = new ToggleSwitch ("Position Spammer", BELOW (ba_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::PositionSpammer::enabled);
	AddComponent (ts_position_spammer);

	ts_position_spammer_say_team = new ToggleSwitch ("Team Chat", STACK (ts_position_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::PositionSpammer::say_team);
	AddComponent (ts_position_spammer_say_team);

	ts_kill_spammer = new ToggleSwitch ("Kill Spammer", BELOW (ts_position_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::KillSpammer::enabled);
	AddComponent (ts_kill_spammer);

	ts_kill_spammer_say_team = new ToggleSwitch ("Team Chat", STACK (ts_kill_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::KillSpammer::say_team);
	AddComponent (ts_kill_spammer_say_team);

	ts_normal_spammer = new ToggleSwitch ("Chat Spammer", BELOW (ts_kill_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::NormalSpammer::enabled);
	AddComponent (ts_normal_spammer);

	ts_normal_spammer_say_team = new ToggleSwitch ("Team Chat", STACK (ts_normal_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::NormalSpammer::say_team);
	AddComponent (ts_normal_spammer_say_team);

	ba_other = new Banner ("Other", STACK (ba_movement), (size.x - 20) / 2 - 5);
	AddComponent (ba_other);

	ts_noflash = new ToggleSwitch ("No Flash", BELOW (ba_other), LOC((size.x - 20) / 6.75, 30), &Settings::Noflash::enabled);
	AddComponent (ts_noflash);

	sl_noflash_value = new Slider ("", STACK (ts_noflash), LOC ((size.x / 2) - ts_noflash->size.x - 30, 30), &Settings::Noflash::value, 0.0f, 255.0f);
	AddComponent (sl_noflash_value);

	ts_fov = new ToggleSwitch ("View FOV", BELOW (ts_noflash), LOC((size.x - 20) / 6.75, 30), &Settings::FOVChanger::enabled);
	AddComponent (ts_fov);

	sl_fov_value = new Slider ("", STACK (ts_fov), LOC ((size.x / 2) - ts_fov->size.x - 30, 30), &Settings::FOVChanger::value, 0.0f, 180.0f);
	AddComponent (sl_fov_value);

	ts_fov_viewmodel = new ToggleSwitch ("Viewmodel FOV", BELOW (ts_fov), LOC((size.x - 20) / 6.75, 30), &Settings::FOVChanger::viewmodel_enabled);
	AddComponent (ts_fov_viewmodel);

	sl_fov_viewmodel_value = new Slider ("", STACK (ts_fov_viewmodel), LOC ((size.x / 2) - ts_fov_viewmodel->size.x - 30, 30), &Settings::FOVChanger::viewmodel_value, 0.0f, 360.0f);
	AddComponent (sl_fov_viewmodel_value);

	ts_fakelag = new ToggleSwitch ("Fake Lag", BELOW (ts_fov_viewmodel), LOC((size.x - 20) / 6.75, 30), &Settings::FakeLag::enabled);
	AddComponent (ts_fakelag);

	sl_fakelag = new Slider_INT ("", STACK (ts_fakelag), LOC ((size.x / 2) - ts_fakelag->size.x - 30, 33), &Settings::FakeLag::value, 0, 16);
	AddComponent (sl_fakelag);

	ts_radar = new ToggleSwitch ("Radar", BELOW (ts_fakelag), LOC((size.x - 20) / 6.75, 30), &Settings::Radar::enabled);
	AddComponent (ts_radar);

	ts_showranks = new ToggleSwitch ("Show Ranks", BELOW (ts_radar), LOC((size.x - 20) / 6.75, 30), &Settings::ShowRanks::enabled);
	AddComponent (ts_showranks);

	ts_showspectators = new ToggleSwitch ("Show Spectators", STACK (ts_showranks), LOC((size.x - 20) / 6.75, 30), &Settings::ShowSpectators::enabled);
	AddComponent (ts_showspectators);

	ts_clantag = new ToggleSwitch ("Custom Clantag", BELOW (ts_showranks), LOC((size.x - 20) / 6.75, 30), &Settings::ClanTagChanger::enabled);
	AddComponent (ts_clantag);

	tb_clantag = new TextBox ("Clantag", &Settings::ClanTagChanger::value, STACK (ts_clantag), LOC((size.x - 20) / 6.75, 30));
	AddComponent (tb_clantag);

	ts_clantag_animation = new ToggleSwitch ("Clantag Animation", BELOW (ts_clantag), LOC((size.x - 20) / 6.75, 30), &Settings::ClanTagChanger::animation);
	AddComponent (ts_clantag_animation);

	vtb_nickname = new ValueTextBox ("Nickname", "", BELOW (ts_clantag_animation), LOC((size.x - 20) / 6.75, 30));
	AddComponent (vtb_nickname);

	ob_nickname = new OutlinedButton ("Set Nickname", STACK (vtb_nickname), LOC((size.x - 20) / 6.75, 30));
	ob_nickname->OnClickedEvent = MFUNC (&MiscPanel::ob_nickname_clicked, this);
	AddComponent (ob_nickname);

	ob_noname = new OutlinedButton ("No Name", BELOW (vtb_nickname), LOC((size.x - 20) / 6.75, 30));
	ob_noname->OnClickedEvent = MFUNC (&MiscPanel::ob_noname_clicked, this);
	AddComponent (ob_noname);

	ba_colors = new Banner ("Colors", BELOW (ob_noname), (size.x - 20) / 2 - 5);
	AddComponent (ba_colors);

	int x_wide = ba_colors->size.x / 4;

	bn_ui_color = new OutlinedButton ("Main UI", BELOW (ba_colors), LOC((size.x - 20) / 6.75, 30));
	bn_ui_color->OnClickedEvent = MFUNC (&MiscPanel::bn_ui_color_clicked, this);
	AddComponent (bn_ui_color);

	bn_2_color = new OutlinedButton ("X", STACK (bn_ui_color), LOC((size.x - 20) / 6.75, 30));
	AddComponent (bn_2_color);

	bn_3_color = new OutlinedButton ("XX", STACK (bn_2_color), LOC((size.x - 20) / 6.75, 30));
	AddComponent (bn_3_color);

	Hide ();
}

void MiscPanel::ob_nickname_clicked ()
{
	std::string name = std::string(vtb_nickname->text);
	Util::StdReplaceStr(name, "\\n", "\n");

	NameChanger::SetName(name.c_str());
}

void MiscPanel::ob_noname_clicked ()
{
	NameChanger::changes = -1;
	Settings::NameChanger::enabled = true;
	Settings::NameChanger::last_blank = true;
}

void MiscPanel::bn_ui_color_clicked ()
{
	static PopupColorWindow* wn_pop_color = new PopupColorWindow ("UI Main Color", LOC(420, 270), LOC(100,100), Color(0, 0, 0, 0), &Settings::UI::mainColor);


	if (!wn_pop_color->IsShown())
	{
		gui->AddWindow (wn_pop_color);
		wn_pop_color->OnShown ();
		wn_pop_color->Show ();
	}
	else
	{
		wn_pop_color->Destroy ();
	}
}
