#pragma once

class KnifeSkinPanel;

#include "../UI/stdui.h"
#include "../atgui.h"


class KnifeSkinPanel : public Panel
{
private:
  TextBox* skinIDTextBox;
  TextBox* seedIDTextBox;
  Slider* wearAmountSlider;
  TextBox* stattrakTextBox;
  TextBox* nameIDTextBox;
  OutlinedButton* setButton;
  float wearAmount = 0.0f;
  std::string skinIDText;
  std::string seedIDText;
  std::string stattrakText;
  std::string nameIDText;
  ItemDefinitionIndex knifeType;
  ScrollingListBox<ItemDefinitionIndex>* slb_knife;

  void ApplySkin();
  //std::string WeaponSkinPanel::convertToUpper();
public:
  KnifeSkinPanel(Vector2D position, Vector2D size);
};
