#include "main_window.h"

MainWindow* main_window = nullptr;

MainWindow::MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	aimbot_button = new OutlinedButton ("AimBot", LOC (10, 10), LOC (size.x - 20, 40));
	AddComponent (aimbot_button);
	
	aimbot_button->OnClickedEvent = MFUNC (&MainWindow::aimbot_button_clicked, this);
	
	esp_button = new OutlinedButton ("Visuals", LOC (10, aimbot_button->position.y + aimbot_button->size.y + 10), LOC (size.x - 20, 40));
	AddComponent (esp_button);
	
	esp_button->OnClickedEvent = MFUNC (&MainWindow::esp_button_clicked, this);
	
	hvh_button = new OutlinedButton ("H V H", LOC (10, esp_button->position.y + esp_button->size.y + 10), LOC (size.x - 20, 40));
	AddComponent (hvh_button);
	
	hvh_button->OnClickedEvent = MFUNC (&MainWindow::hvh_button_clicked, this);
	
	misc_button = new OutlinedButton ("Miscellaneous", LOC (10, hvh_button->position.y + hvh_button->size.y + 10), LOC (size.x - 20, 40));
	AddComponent (misc_button);
	
	misc_button->OnClickedEvent = MFUNC (&MainWindow::misc_button_clicked, this);

	load1_button = new OutlinedButton ("Load #1", LOC (10, misc_button->position.y + misc_button->size.y + 10), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (load1_button);

	load1_button->OnClickedEvent = MFUNC (&MainWindow::load1_button_clicked, this);

	load2_button = new OutlinedButton ("Load #2", LOC (load1_button->position.x + (size.x - 20) / 2 + 5, misc_button->position.y + misc_button->size.y + 10), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (load2_button);

	load2_button->OnClickedEvent = MFUNC (&MainWindow::load2_button_clicked, this);

	save1_button = new OutlinedButton ("Save #1", LOC (10, load1_button->position.y + load1_button->size.y + 10), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (save1_button);

	save1_button->OnClickedEvent = MFUNC (&MainWindow::save1_button_clicked, this);

	save2_button = new OutlinedButton ("Save #2", LOC (save1_button->position.x + (size.x - 20) / 2 + 5, load1_button->position.y + load1_button->size.y + 10), LOC ((size.x - 20) / 2 - 5, 40));
	AddComponent (save2_button);

	save2_button->OnClickedEvent = MFUNC (&MainWindow::save2_button_clicked, this);

	Show ();
}

void MainWindow::aimbot_button_clicked ()
{
	aimbot_window->Toggle ();
}

void MainWindow::esp_button_clicked ()
{
	esp_window->Toggle ();
}

void MainWindow::misc_button_clicked ()
{
	misc_window->Toggle ();
}

void MainWindow::hvh_button_clicked ()
{
	hvh_window->Toggle ();
}

void MainWindow::load1_button_clicked ()
{
	Settings::LoadSettings("aimtux_settings_1");
}

void MainWindow::load2_button_clicked ()
{
	Settings::LoadSettings("aimtux_settings_2");
}

void MainWindow::save1_button_clicked ()
{
	Settings::LoadDefaultsOrSave("aimtux_settings_1");
}

void MainWindow::save2_button_clicked ()
{
	Settings::LoadDefaultsOrSave("aimtux_settings_2");
}