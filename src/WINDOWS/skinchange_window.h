#pragma once

class SkinChangerWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class SkinChangerWindow : public Window
{
protected:
  TabSelector* tabSelector;

  Panel* knifeskin_panel;
  Panel* weaponskin_panel;
  
public:
  SkinChangerWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
};
