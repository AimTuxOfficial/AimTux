#pragma once

class MiscPanel;

#include "../UI/stdui.h"
#include "../atgui.h"
#include "../util.h"

class MiscPanel : public Panel
{
private:
	Banner* ba_movement;
	ToggleSwitch* ts_bhop;
	ToggleSwitch* ts_autostrafe;
	ToggleSwitch* ts_airstuck;
	Banner* ba_spammer;
	ToggleSwitch* ts_spammer;
	ToggleSwitch* ts_spammer_kill;
	Banner* ba_other;
	ToggleSwitch* ts_noflash;
	Slider* sl_noflash_value;
	ToggleSwitch* ts_showranks;
	ToggleSwitch* ts_showspectators;
	ToggleSwitch* ts_clantag;
	TextBox* tb_clantag;
	ToggleSwitch* ts_clantag_animation;
public:
	MiscPanel (Vector2D position, Vector2D size);
};