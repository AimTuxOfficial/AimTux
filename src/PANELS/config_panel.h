
#pragma once

class SkinChangerPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class ConfigPanel : public Panel
{
private:
	ListBox_Config* lb_configs;
	OutlinedButton* bn_refresh;
	OutlinedButton* bn_remove;
	OutlinedButton* bn_save;
public:
	ConfigPanel(Vector2D position, Vector2D size);
	void bn_refresh_clicked ();
	void bn_remove_clicked ();
	void bn_save_clicked ();
};