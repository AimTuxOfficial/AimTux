#pragma once

class SkinChangerPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class SkinChangerPanel : public Panel
{
private:
	Banner* ba_gun;
	Banner* ba_knife;

	TextBox* gunIDTextBox;
	NumberBox* gunSkinIDTextBox;
	NumberBox* gunSeedIDTextBox;
	Slider* gunWearAmountSlider;
	NumberBox* gunStattrakTextBox;
	TextBox* gunNameIDTextBox;
	float gunWearAmount = 0.005f;
	OutlinedButton* gunSetButton;
	OutlinedButton* gunLoadButton;
	ItemDefinitionIndex gun;
	ComboBox<ItemDefinitionIndex>* cb_gun;
	std::string gunIDText;
	std::string gunSkinIDText;
	std::string gunSeedIDText;
	std::string gunStattrakText;
	std::string gunNameIDText;

	NumberBox* knifeSkinIDTextBox;
	NumberBox* knifeSeedIDTextBox;
	Slider* knifeWearAmountSlider;
	NumberBox* knifeStattrakTextBox;
	TextBox* knifeNameIDTextBox;
	float knifeWearAmount = 0.005f;
	OutlinedButton* knifeSetButton;
	OutlinedButton* knifeLoadButton;
	ItemDefinitionIndex knife;
	ComboBox<ItemDefinitionIndex>* cb_knife;
	enum Side : unsigned int { CT,	T };
	Side side;
	ComboBox<Side>* cb_side;
	std::string knifeSkinIDText;
	std::string knifeSeedIDText;
	std::string knifeStattrakText;
	std::string knifeNameIDText;

	void ApplyGunSkin();
	void ApplyKnifeSkin();
	void LoadGunSkin();
	void LoadKnifeSkin();

public:
	SkinChangerPanel(Vector2D position, Vector2D size);
};
