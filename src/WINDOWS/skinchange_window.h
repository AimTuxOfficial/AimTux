#pragma once

class SkinChangerWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class SkinChangerWindow : public Window
{
protected:
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
  SkinChangerWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};
