#pragma once

class WeaponSkinPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class WeaponSkinPanel : public Panel
{
private:
	TextBox* weaponIDTextBox;
	TextBox* skinIDTextBox;
	TextBox* seedIDTextBox;
	Slider* wearAmountSlider;
	TextBox* stattrakTextBox;
	TextBox* nameIDTextBox;
	OutlinedButton* setButton;
	float wearAmount = 0.0f;
	std::string weaponIDText;
	std::string skinIDText;
	std::string seedIDText;
	std::string stattrakText;
	std::string nameIDText;

	void ApplySkin();
public:
	WeaponSkinPanel (Vector2D position, Vector2D size);
};
