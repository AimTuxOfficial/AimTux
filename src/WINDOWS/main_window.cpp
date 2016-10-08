#include "main_window.h"

MainWindow* main_window = nullptr;

MainWindow::MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	aimbot_button = new OutlinedButton ("AimBot", LOC (10, 10), LOC (size.x-20, 40));
	AddComponent (aimbot_button);
	
	aimbot_button->OnClickedEvent = MFUNC (&MainWindow::aimbot_button_clicked, this);
	
	esp_button = new OutlinedButton ("Visuals", LOC (10, aimbot_button->position.y + aimbot_button->size.y + 10), LOC (size.x-20, 40));
	AddComponent (esp_button);
	
	esp_button->OnClickedEvent = MFUNC (&MainWindow::esp_button_clicked, this);
	
	hvh_button = new OutlinedButton ("H V H", LOC (10, esp_button->position.y + esp_button->size.y + 10), LOC (size.x-20, 40));
	AddComponent (hvh_button);
	
	hvh_button->OnClickedEvent = MFUNC (&MainWindow::hvh_button_clicked, this);
	
	misc_button = new OutlinedButton ("Miscellaneous", LOC (10, hvh_button->position.y + hvh_button->size.y + 10), LOC (size.x-20, 40));
	AddComponent (misc_button);
	
	misc_button->OnClickedEvent = MFUNC (&MainWindow::misc_button_clicked, this);

	load_button = new OutlinedButton ("Load configuration", LOC (10, misc_button->position.y + misc_button->size.y + 10), LOC (size.x-20, 40));
	AddComponent (load_button);

	load_button->OnClickedEvent = MFUNC (&MainWindow::load_button_clicked, this);

	save_button = new OutlinedButton ("Save configuration", LOC (10, load_button->position.y + load_button->size.y + 10), LOC (size.x-20, 40));
	AddComponent (save_button);

	save_button->OnClickedEvent = MFUNC (&MainWindow::save_button_clicked, this);

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

void MainWindow::load_button_clicked ()
{
	Settings::LoadSettings();
}

void MainWindow::save_button_clicked ()
{
	Settings::LoadDefaultsOrSave();
}