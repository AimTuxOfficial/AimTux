#include <stdlib.h>
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
	vtb_add = new ValueTextBox ("Config name", "", BELOW (bn_refresh), LOC(310, 30));
	ob_add = new OutlinedButton ("Add", STACK (vtb_add), LOC(150, 30));
	ob_add->OnClickedEvent = MFUNC (&ConfigPanel::ob_add_clicked, this);
	lb_configs = new ListBox_Config ("Configs", BELOW (vtb_add), bn_save->position.x + bn_save->size.x - 10);

	AddComponent (lb_configs);
	AddComponent (bn_refresh);
	AddComponent (bn_remove);
	AddComponent (bn_save);
	AddComponent (ob_add);
	AddComponent (vtb_add);

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

void ConfigPanel::ob_add_clicked()
{
	if (vtb_add->text.length() == 0)
		return;

	pstring path = getenv("HOME");
	path << "/.config" << "/AimTux/" << vtb_add->text;

	if (DoesFileExist(path.c_str()))
		return;

	mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	Config new_config(vtb_add->text.c_str(), path.c_str());
	Settings::LoadDefaultsOrSave(new_config);

	bn_refresh_clicked ();
}