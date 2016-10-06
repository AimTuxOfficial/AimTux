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
	ToggleSwitch* ts_noflash;
	ToggleSwitch* ts_rainbow_cham_hands;
	ToggleSwitch* ts_airstuck;
public:
	MiscWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};

#endif
