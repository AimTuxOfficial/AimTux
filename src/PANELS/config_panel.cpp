#include "config_panel.h"

ConfigPanel::ConfigPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	lb_configs = new ListBox_Config ("Configs", LOC (size.x / 3, 10), size.x / 3);
	bn_refresh = new OutlinedButton ("Refresh", STACK (lb_configs), LOC (150, 30));
	bn_refresh->OnClickedEvent = MFUNC (&ConfigPanel::bn_refresh_clicked, this);
	
	AddComponent (lb_configs);
	AddComponent (bn_refresh);
	
	Hide ();
}

void ConfigPanel::bn_refresh_clicked ()
{
	Settings::LoadSettings ();
	lb_configs->Reload();
}