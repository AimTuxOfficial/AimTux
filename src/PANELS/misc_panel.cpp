#include "misc_panel.h"

MiscPanel::MiscPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ts_bhop = new ToggleSwitch ("bhop", LOC (10, 10), 33, &Settings::BHop::enabled);
	AddComponent (ts_bhop);
	
	ts_autostrafe = new ToggleSwitch ("auto strafe", BELOW (ts_bhop), 33, &Settings::AutoStrafe::enabled);
	AddComponent (ts_autostrafe);
	
	ts_spammer = new ToggleSwitch ("chat spammer", BELOW (ts_autostrafe), 33, &Settings::Spammer::NormalSpammer::enabled);
	AddComponent (ts_spammer);
	
	ts_spammer_kill = new ToggleSwitch ("kill spammer", STACK (ts_spammer), 33, &Settings::Spammer::KillSpammer::enabled);
	AddComponent (ts_spammer_kill);

	ts_airstuck = new ToggleSwitch ("airstuck", BELOW (ts_spammer), 33, &Settings::Airstuck::enabled);
	AddComponent (ts_airstuck);

	ts_showranks = new ToggleSwitch ("show ranks", BELOW (ts_airstuck), 33, &Settings::ShowRanks::enabled);
	AddComponent (ts_showranks);

	ts_showspectators = new ToggleSwitch ("show spectators", STACK (ts_showranks), 33, &Settings::ShowSpectators::enabled);
	AddComponent (ts_showspectators);

	ts_noflash = new ToggleSwitch ("no flash", BELOW (ts_showranks), 33, &Settings::Noflash::enabled);
	AddComponent (ts_noflash);
	
	sl_noflash_value = new Slider ("", STACK (ts_noflash), LOC (size.x - ts_noflash->size.x - 30, 33), &Settings::Noflash::value, 0.0f, 255.0f);
	AddComponent (sl_noflash_value);

    // clantag

	ts_clantag = new ToggleSwitch ("custom clantag", BELOW (ts_noflash), 33, &Settings::ClanTagChanger::enabled);
	AddComponent (ts_clantag);

	tb_clantag = new TextBox ("clantag", &Settings::ClanTagChanger::value, STACK (ts_clantag), LOC (270, 33));
	AddComponent (tb_clantag);
	
	
	ts_clantag_animation = new ToggleSwitch ("clantag animation", BELOW (ts_clantag), 33, &Settings::ClanTagChanger::animation);
	AddComponent (ts_clantag_animation);
	
	Hide ();
}
