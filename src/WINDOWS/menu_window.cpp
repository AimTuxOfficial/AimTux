#include "menu_window.h"

MenuWindow* menu_window = nullptr;

MenuWindow::MenuWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, false)
{

	triggerbot_button = new ToggleButton ("TriggerBot", LOC(10, 10), LOC (size.x - 20, 40), &triggerbot_window->shown);
	AddComponent (triggerbot_button);
	
	esp_button = new ToggleButton ("Visuals", BELOW (triggerbot_button), LOC (size.x - 20, 40), &esp_window->shown);
	AddComponent (esp_button);
	
	hvh_button = new ToggleButton ("H V H", BELOW (esp_button), LOC (size.x - 20, 40), &hvh_window->shown);
	AddComponent (hvh_button);
	
	misc_button = new ToggleButton ("Miscellaneous", BELOW (hvh_button), LOC (size.x - 20, 40), &misc_window->shown);
	AddComponent (misc_button);
	
	newui_button = new ToggleButton ("New UI", BELOW (misc_button), LOC (size.x - 20, 40), &main_window->shown);
	AddComponent (newui_button);
	
	load1_button = new OutlinedButton ("Load #1", BELOW (newui_button), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (load1_button);

	load1_button->OnClickedEvent = MFUNC (&MenuWindow::load1_button_clicked, this);

	load2_button = new OutlinedButton ("Load #2", STACK (load1_button), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (load2_button);

	load2_button->OnClickedEvent = MFUNC (&MenuWindow::load2_button_clicked, this);

	save1_button = new OutlinedButton ("Save #1", BELOW (load1_button), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (save1_button);

	save1_button->OnClickedEvent = MFUNC (&MenuWindow::save1_button_clicked, this);

	save2_button = new OutlinedButton ("Save #2", STACK (save1_button), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (save2_button);

	save2_button->OnClickedEvent = MFUNC (&MenuWindow::save2_button_clicked, this);

	Show ();
}

void MenuWindow::load1_button_clicked ()
{
	Settings::LoadSettings("aimtux_settings_1");
}

void MenuWindow::load2_button_clicked ()
{
	Settings::LoadSettings("aimtux_settings_2");
}

void MenuWindow::save1_button_clicked ()
{
	Settings::LoadDefaultsOrSave("aimtux_settings_1");
}

void MenuWindow::save2_button_clicked ()
{
	Settings::LoadDefaultsOrSave("aimtux_settings_2");
}
