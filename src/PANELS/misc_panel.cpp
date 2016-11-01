#include "misc_panel.h"

MiscPanel::MiscPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ba_movement = new Banner ("Movement", LOC (10, 10), (size.x - 20) / 2 - 5);
	AddComponent (ba_movement);

	ts_bhop = new ToggleSwitch ("bhop", BELOW (ba_movement), 33, &Settings::BHop::enabled);
	AddComponent (ts_bhop);
	
	ts_autostrafe = new ToggleSwitch ("auto strafe", BELOW (ts_bhop), 33, &Settings::AutoStrafe::enabled);
	AddComponent (ts_autostrafe);

	ts_airstuck = new ToggleSwitch ("airstuck", BELOW (ts_autostrafe), 33, &Settings::Airstuck::enabled);
	AddComponent (ts_airstuck);

	ba_spammer = new Banner ("Spammer", BELOW (ts_airstuck), (size.x - 20) / 2 - 5);
	AddComponent (ba_spammer);

	ts_position_spammer = new ToggleSwitch ("position spammer", BELOW (ba_spammer), 33, &Settings::Spammer::PositionSpammer::enabled);
	AddComponent (ts_position_spammer);

	ts_kill_spammer = new ToggleSwitch ("kill spammer", BELOW (ts_position_spammer), 33, &Settings::Spammer::KillSpammer::enabled);
	AddComponent (ts_kill_spammer);

	ts_normal_spammer = new ToggleSwitch ("chat spammer", BELOW (ts_kill_spammer), 33, &Settings::Spammer::NormalSpammer::enabled);
	AddComponent (ts_normal_spammer);

	ba_other = new Banner ("Other", STACK (ba_movement), (size.x - 20) / 2 - 5);
	AddComponent (ba_other);

	ts_noflash = new ToggleSwitch ("no flash", BELOW (ba_other), 33, &Settings::Noflash::enabled);
	AddComponent (ts_noflash);

	sl_noflash_value = new Slider ("", STACK (ts_noflash), LOC ((size.x / 2) - ts_noflash->size.x - 30, 33), &Settings::Noflash::value, 0.0f, 255.0f);
	AddComponent (sl_noflash_value);

	ts_fov = new ToggleSwitch ("view fov", BELOW (ts_noflash), 33, &Settings::FOVChanger::enabled);
	AddComponent (ts_fov);

	sl_fov_value = new Slider ("", STACK (ts_fov), LOC ((size.x / 2) - ts_fov->size.x - 30, 33), &Settings::FOVChanger::value, 0.0f, 180.0f);
	AddComponent (sl_fov_value);

	ts_fov_viewmodel = new ToggleSwitch ("viewmodel fov", BELOW (ts_fov), 33, &Settings::FOVChanger::viewmodel_enabled);
	AddComponent (ts_fov_viewmodel);

	sl_fov_viewmodel_value = new Slider ("", STACK (ts_fov_viewmodel), LOC ((size.x / 2) - ts_fov_viewmodel->size.x - 30, 33), &Settings::FOVChanger::viewmodel_value, 0.0f, 360.0f);
	AddComponent (sl_fov_viewmodel_value);

	ts_radar = new ToggleSwitch ("radar", BELOW (ts_fov_viewmodel), 33, &Settings::Radar::enabled);
	AddComponent (ts_radar);

#ifdef EXPERIMENTAL_SETTINGS
	ts_fakelag = new ToggleSwitch ("fake lag", BELOW (ts_radar), 33, &Settings::FakeLag::enabled);
	AddComponent (ts_fakelag);

	ts_showranks = new ToggleSwitch ("show ranks", BELOW (ts_fakelag), 33, &Settings::ShowRanks::enabled);
#else
	ts_showranks = new ToggleSwitch ("show ranks", BELOW (ts_radar), 33, &Settings::ShowRanks::enabled);
#endif
	AddComponent (ts_showranks);

	ts_showspectators = new ToggleSwitch ("show spectators", BELOW (ts_showranks), 33, &Settings::ShowSpectators::enabled);
	AddComponent (ts_showspectators);

#ifdef UNTRUSTED_SETTINGS
	ts_teleport = new ToggleSwitch ("teleport", BELOW (ts_showspectators), 33, &Settings::Teleport::enabled);
	AddComponent (ts_teleport);

	ts_clantag = new ToggleSwitch ("custom clantag", BELOW (ts_teleport), 33, &Settings::ClanTagChanger::enabled);
#else
	ts_clantag = new ToggleSwitch ("custom clantag", BELOW (ts_showspectators), 33, &Settings::ClanTagChanger::enabled);
#endif
	AddComponent (ts_clantag);

	tb_clantag = new TextBox ("clantag", &Settings::ClanTagChanger::value, STACK (ts_clantag), LOC (270, 33));
	AddComponent (tb_clantag);
	
	ts_clantag_animation = new ToggleSwitch ("clantag animation", BELOW (ts_clantag), 33, &Settings::ClanTagChanger::animation);
	AddComponent (ts_clantag_animation);

	vtb_nickname = new ValueTextBox ("nickname", "", BELOW (ts_clantag_animation), LOC (270, 33));
	AddComponent (vtb_nickname);

	ob_nickname = new OutlinedButton ("set nickname", STACK (vtb_nickname), LOC (120, 33));
	ob_nickname->OnClickedEvent = MFUNC (&MiscPanel::ob_nickname_clicked, this);
	AddComponent (ob_nickname);

	ob_noname = new OutlinedButton ("no name", BELOW (vtb_nickname), LOC (120, 33));
	ob_noname->OnClickedEvent = MFUNC (&MiscPanel::ob_noname_clicked, this);
	AddComponent (ob_noname);
	
	ba_colors = new Banner ("Colors", BELOW (ob_noname), (size.x - 20) / 2 - 5);
	AddComponent (ba_colors); 
	
	int x_wide = ba_colors->size.x / 4;
	
	bn_ui_color = new OutlinedButton ("Main UI", BELOW (ba_colors), LOC (x_wide, 33));
	bn_ui_color->OnClickedEvent = MFUNC (&MiscPanel::bn_ui_color_clicked, this);
	AddComponent (bn_ui_color);
	
	bn_2_color = new OutlinedButton ("X", STACK (bn_ui_color), LOC (x_wide - 10, 33));
	AddComponent (bn_2_color);
	
	bn_3_color = new OutlinedButton ("XX", STACK (bn_2_color), LOC (x_wide - 20, 33));
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
	static PopupColorWindow* wn_pop_color = new PopupColorWindow ("UI Main Color", LOC(420, 400), LOC(100,100), Color(0, 0, 0, 0), &Settings::UI::mainColor);
	
	
	if (!wn_pop_color->IsShown())
	{
		gui->AddWindow (wn_pop_color);
		wn_pop_color->Show ();
	}
	else
	{
		wn_pop_color->Destroy ();
	}
}