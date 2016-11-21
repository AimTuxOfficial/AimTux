#include "config_panel.h"

ConfigPanel::ConfigPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	lb_configs = new ListBox_Config ("Configs", LOC (size.x / 3, 10), size.x / 3);
	
	
	AddComponent (lb_configs);
	
	Hide ();
}