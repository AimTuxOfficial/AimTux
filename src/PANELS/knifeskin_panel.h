#pragma once

class KnifeSkinPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class KnifeSkinPanel : public Panel
{
private:
	NumberBox* skinIDTextBox;
	NumberBox* seedIDTextBox;
	Slider* wearAmountSlider;
	NumberBox* stattrakTextBox;
	TextBox* nameIDTextBox;
	OutlinedButton* loadButton;
	OutlinedButton* setButton;
	float wearAmount = 0.005f;
	std::string skinIDText;
	std::string seedIDText;
	std::string stattrakText;
	std::string nameIDText;
	ItemDefinitionIndex knifeType;
	ScrollingListBox<ItemDefinitionIndex>* slb_knife;
	enum Side : unsigned int
	{
		CT,
		T
	};
	Side side;
	ComboBox<Side>* cb_side;

	void LoadSkin();
	void ApplySkin();
public:
	KnifeSkinPanel(Vector2D position, Vector2D size);
};
