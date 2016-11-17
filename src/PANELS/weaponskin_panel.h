#pragma once

class WeaponSkinPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class WeaponSkinPanel : public Panel
{
private:
	TextBox* weaponIDTextBox;
	NumberBox* skinIDTextBox;
	NumberBox* seedIDTextBox;
	Slider* wearAmountSlider;
	NumberBox* stattrakTextBox;
	TextBox* nameIDTextBox;
	OutlinedButton* loadButton;
	OutlinedButton* setButton;
	float wearAmount = 0.005f;
	std::string weaponIDText;
	std::string skinIDText;
	std::string seedIDText;
	std::string stattrakText;
	std::string nameIDText;

	void LoadSkin();
	void ApplySkin();
public:
	WeaponSkinPanel (Vector2D position, Vector2D size);
};
