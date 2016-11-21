#include "config_panel.h"

ConfigPanel::ConfigPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	bn_refresh = new OutlinedButton ("Refresh", LOC (10, 10), LOC (150, 30));
	bn_refresh->OnClickedEvent = MFUNC (&ConfigPanel::bn_refresh_clicked, this);
	bn_remove = new OutlinedButton ("Remove", STACK (bn_refresh), LOC (150, 30));
	bn_remove->OnClickedEvent = MFUNC (&ConfigPanel::bn_remove_clicked, this);
	bn_save = new OutlinedButton ("Save", STACK (bn_remove), LOC (150, 30));
	bn_save->OnClickedEvent = MFUNC (&ConfigPanel::bn_save_clicked, this);
	lb_configs = new ListBox_Config ("Configs", BELOW (bn_refresh), bn_save->position.x + bn_save->size.x - 10);

	AddComponent (lb_configs);
	AddComponent (bn_refresh);
	AddComponent (bn_remove);
	AddComponent (bn_save);

	Hide ();
}

void ConfigPanel::bn_refresh_clicked ()
{
	Settings::LoadSettings ();
	lb_configs->Reload();
}

void ConfigPanel::bn_remove_clicked ()
{
	if (current_config == nullptr)
		return;
	
	Settings::DeleteConfig (*current_config);
	Settings::LoadSettings ();
	lb_configs->Reload();
	
	current_config = nullptr;
}

void ConfigPanel::bn_save_clicked ()
{
	if (current_config == nullptr)
		return;

	Settings::LoadDefaultsOrSave(*current_config);
}