#pragma once

class SkinChangePanel;

#include "../UI/stdui.h"
#include "../atgui.h"
#include "../Hooks/hooks.h"

class SkinChangePanel : public Panel
{
private:
  StackedListBox<KnifeType>* lb_knifetype;

  Button* updateButton;

  void UpdateButtonClicked();
public:
  SkinChangePanel (Vector2D position, Vector2D size);
};
