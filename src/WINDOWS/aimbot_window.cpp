#include "aimbot_window.h"

AimbotWindow* aimbot_window = nullptr;

AimbotWindow::AimbotWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor)
{
	ts_aimbot_enabled = new ToggleSwitch ("aimbot", LOC (10, 10), 35, &Settings::Aimbot::enabled);
	AddComponent (ts_aimbot_enabled);
	
	ts_rcs = new ToggleSwitch ("recoil control", LOC (10, ts_aimbot_enabled->position.y + ts_aimbot_enabled->size.y + 10), 35, &Settings::Aimbot::RCS::enabled);
	AddComponent (ts_rcs);
	
	ts_silent = new ToggleSwitch ("silent aim", LOC (10, ts_rcs->position.y + ts_rcs->size.y + 10), 35, &Settings::Aimbot::silent);
	AddComponent (ts_silent);
	
	ts_autoaim = new ToggleSwitch ("auto aim", LOC (10, ts_silent->position.y + ts_silent->size.y + 10), 35, &Settings::Aimbot::AutoAim::enabled);
	AddComponent (ts_autoaim);

	sl_fov = new Slider ("fov", LOC (ts_autoaim->position.x + ts_autoaim->size.x + 10, ts_autoaim->position.y), LOC (size.x - ts_autoaim->size.x - 30, 35), &Settings::Aimbot::fov, 0.0f, 180.0f);
	AddComponent (sl_fov);
	
	
	ts_smooth_enable = new ToggleSwitch ("smooth", LOC (10, ts_autoaim->position.y + ts_autoaim->size.y + 10), 35, &Settings::Aimbot::Smooth::enabled);
	AddComponent (ts_smooth_enable);
	
	sl_smooth_value = new Slider ("smooth", LOC (ts_smooth_enable->position.x + ts_smooth_enable->size.x + 10, ts_smooth_enable->position.y), LOC (size.x - ts_smooth_enable->size.x - 30, 35), &Settings::Aimbot::Smooth::value, 0.10f, Settings::Aimbot::Smooth::max);
	AddComponent (sl_smooth_value);
	
	
	ts_aimstep = new ToggleSwitch ("aim step", LOC (10, ts_smooth_enable->position.y + ts_smooth_enable->size.y + 10), 35, &Settings::Aimbot::AimStep::enabled);
	AddComponent (ts_aimstep);
	
	ts_autoshoot = new ToggleSwitch ("auto shoot", LOC (10, ts_aimstep->position.y + ts_aimstep->size.y + 10), 35, &Settings::Aimbot::AutoShoot::enabled);
	AddComponent (ts_autoshoot);
	
	ts_autocrouch = new ToggleSwitch ("auto crouch", LOC (10, ts_autoshoot->position.y + ts_autoshoot->size.y + 10), 35, &Settings::Aimbot::AutoCrouch::enabled);
	AddComponent (ts_autocrouch);
	
	ts_autostop = new ToggleSwitch ("auto stop", LOC (10, ts_autocrouch->position.y + ts_autocrouch->size.y + 10), 35, &Settings::Aimbot::AutoStop::enabled);
	AddComponent (ts_autostop);
	
	Hide ();
}