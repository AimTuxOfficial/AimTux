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

	ba_other = new Banner ("Other", BELOW (ts_normal_spammer), (size.x - 20) / 2 - 5);
	AddComponent (ba_other);

	ts_noflash = new ToggleSwitch ("no flash", BELOW (ba_other), 33, &Settings::Noflash::enabled);
	AddComponent (ts_noflash);

	sl_noflash_value = new Slider ("", STACK (ts_noflash), LOC ((size.x / 2) - ts_noflash->size.x - 30, 33), &Settings::Noflash::value, 0.0f, 255.0f);
	AddComponent (sl_noflash_value);

	ts_showranks = new ToggleSwitch ("show ranks", BELOW (ts_noflash), 33, &Settings::ShowRanks::enabled);
	AddComponent (ts_showranks);

	ts_showspectators = new ToggleSwitch ("show spectators", BELOW (ts_showranks), 33, &Settings::ShowSpectators::enabled);
	AddComponent (ts_showspectators);

	ts_clantag = new ToggleSwitch ("custom clantag", BELOW (ts_showspectators), 33, &Settings::ClanTagChanger::enabled);
	AddComponent (ts_clantag);

	tb_clantag = new TextBox ("clantag", &Settings::ClanTagChanger::value, STACK (ts_clantag), LOC (270, 33));
	AddComponent (tb_clantag);
	
	ts_clantag_animation = new ToggleSwitch ("clantag animation", BELOW (ts_clantag), 33, &Settings::ClanTagChanger::animation);
	AddComponent (ts_clantag_animation);
	
	Hide ();
}
