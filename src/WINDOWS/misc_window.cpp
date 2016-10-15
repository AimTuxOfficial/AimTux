#include "misc_window.h"

MiscWindow* misc_window = nullptr;

MiscWindow::MiscWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_bhop = new ToggleSwitch ("bhop", LOC (10, 10), 35, &Settings::BHop::enabled);
	AddComponent (ts_bhop);
	
	ts_autostrafe = new ToggleSwitch ("auto strafe", BELOW (ts_bhop), 35, &Settings::AutoStrafe::enabled);
	AddComponent (ts_autostrafe);
	
	ts_spammer = new ToggleSwitch ("chat spammer", BELOW (ts_autostrafe), 35, &Settings::Spammer::NormalSpammer::enabled);
	AddComponent (ts_spammer);
	
	ts_spammer_kill = new ToggleSwitch ("kill spammer", STACK (ts_spammer), 35, &Settings::Spammer::KillSpammer::enabled);
	AddComponent (ts_spammer_kill);

	ts_airstuck = new ToggleSwitch ("airstuck", BELOW (ts_spammer), 35, &Settings::Airstuck::enabled);
	AddComponent (ts_airstuck);

	ts_showranks = new ToggleSwitch ("show ranks", BELOW (ts_airstuck), 35, &Settings::ShowRanks::enabled);
	AddComponent (ts_showranks);

	ts_showspectators = new ToggleSwitch ("show spectators", BELOW (ts_showranks), 35, &Settings::ShowSpectators::enabled);
	AddComponent (ts_showspectators);

	ts_noflash_enabled = new ToggleSwitch ("no flash", BELOW (ts_showspectators), 35, &Settings::Noflash::enabled);
	AddComponent (ts_noflash_enabled);
	
	sl_noflash_value = new Slider ("", STACK (ts_noflash_enabled), LOC (size.x - ts_noflash_enabled->size.x - 30, 35), &Settings::Noflash::value, 0.0f, 255.0f);
	AddComponent (sl_noflash_value);
	
	Hide ();
}
