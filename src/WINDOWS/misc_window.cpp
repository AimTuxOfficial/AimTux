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
	
	ts_noflash = new ToggleSwitch ("no flash", LOC (10, ts_spammer->position.y + ts_spammer->size.y + 10), 35, &Settings::Noflash::enabled);
	AddComponent (ts_noflash);
	
	ts_rainbow_cham_hands = new ToggleSwitch ("rainbow arms", LOC (10, ts_noflash->position.y + ts_noflash->size.y + 10), 35, &Settings::ESP::Chams::rainbow_arms);
	AddComponent (ts_rainbow_cham_hands);

	ts_airstuck = new ToggleSwitch ("airstuck", LOC (10, ts_rainbow_cham_hands->position.y + ts_rainbow_cham_hands->size.y + 10), 35, &Settings::Airstuck::enabled);
	AddComponent (ts_airstuck);
	Hide ();
}
