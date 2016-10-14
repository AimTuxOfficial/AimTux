#include "misc_window.h"

MiscWindow* misc_window = nullptr;

MiscWindow::MiscWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_bhop = new ToggleSwitch ("bhop", LOC (10, 10), 35, &Settings::BHop::enabled);
	AddComponent (ts_bhop);
	
	ts_autostrafe = new ToggleSwitch ("auto strafe", LOC (10, ts_bhop->position.y + ts_bhop->size.y + 10), 35, &Settings::AutoStrafe::enabled);
	AddComponent (ts_autostrafe);
	
	ts_spammer = new ToggleSwitch ("spammer", LOC (10, ts_autostrafe->position.y + ts_autostrafe->size.y + 10), 35, &Settings::Spammer::enabled);
	AddComponent (ts_spammer);

	ts_airstuck = new ToggleSwitch ("airstuck", LOC (10, ts_spammer->position.y + ts_spammer->size.y + 10), 35, &Settings::Airstuck::enabled);
	AddComponent (ts_airstuck);

	ts_showranks = new ToggleSwitch ("show ranks", LOC (10, ts_airstuck->position.y + ts_airstuck->size.y + 10), 35, &Settings::ShowRanks::enabled);
	AddComponent (ts_showranks);

	ts_showspectators = new ToggleSwitch ("show spectators", LOC (10, ts_showranks->position.y + ts_showranks->size.y + 10), 35, &Settings::ShowSpectators::enabled);
	AddComponent (ts_showspectators);

	ts_noflash_enabled = new ToggleSwitch ("no flash", LOC (10, ts_showspectators->position.y + ts_showspectators->size.y + 10), 35, &Settings::Noflash::enabled);
	AddComponent (ts_noflash_enabled);
	
	sl_noflash_value = new Slider ("flash", LOC (ts_noflash_enabled->position.x + ts_noflash_enabled->size.x + 10, ts_noflash_enabled->position.y), LOC (size.x - ts_noflash_enabled->size.x - 30, 35), &Settings::Noflash::value, 0.0f, 255.0f);
	AddComponent (sl_noflash_value);
	
	Hide ();
}
