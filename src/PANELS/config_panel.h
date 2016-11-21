
#pragma once

class SkinChangerPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class ConfigPanel : public Panel
{
private:
	ListBox_Config* lb_configs;
	OutlinedButton* bn_refresh;
public:
	ConfigPanel(Vector2D position, Vector2D size);
	void bn_refresh_clicked ();
};