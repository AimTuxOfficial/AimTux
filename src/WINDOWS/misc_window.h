#ifndef __MISC_WINDOW_H_
#define __MISC_WINDOW_H_

class MiscWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class MiscWindow : public Window
{
private:
	ToggleSwitch* ts_bhop;
	ToggleSwitch* ts_autostrafe;
	ToggleSwitch* ts_spammer;
	ToggleSwitch* ts_spammer_kill;
	ToggleSwitch* ts_airstuck;
	ToggleSwitch* ts_showranks;
	ToggleSwitch* ts_showspectators;
	ToggleSwitch* ts_noflash_enabled;
	Slider* sl_noflash_value;
	TextBox* tb_clantag;
	OutlinedButton* ob_clantag_set;
public:
	MiscWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
	void SetClanTag ();
};

extern SendClanTagFn SendClanTag;

#endif
