#include "config_window.h"

ConfigWindow* config_window = nullptr;

ConfigWindow::ConfigWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, true)
{
	load1_button = new OutlinedButton ("Load #1", LOC (10, 10), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (load1_button);

	load1_button->OnClickedEvent = MFUNC (&ConfigWindow::load1_button_clicked, this);

	load2_button = new OutlinedButton ("Load #2", STACK (load1_button), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (load2_button);

	load2_button->OnClickedEvent = MFUNC (&ConfigWindow::load2_button_clicked, this);

	save1_button = new OutlinedButton ("Save #1", BELOW (load1_button), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (save1_button);

	save1_button->OnClickedEvent = MFUNC (&ConfigWindow::save1_button_clicked, this);

	save2_button = new OutlinedButton ("Save #2", STACK (save1_button), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (save2_button);

	save2_button->OnClickedEvent = MFUNC (&ConfigWindow::save2_button_clicked, this);

	Show ();
}

void ConfigWindow::load1_button_clicked ()
{
	Settings::LoadSettings("aimtux_settings_1");
}

void ConfigWindow::load2_button_clicked ()
{
	Settings::LoadSettings("aimtux_settings_2");
}

void ConfigWindow::save1_button_clicked ()
{
	Settings::LoadDefaultsOrSave("aimtux_settings_1");
}

void ConfigWindow::save2_button_clicked ()
{
	Settings::LoadDefaultsOrSave("aimtux_settings_2");
}
