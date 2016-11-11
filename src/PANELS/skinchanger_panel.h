#pragma once

class SkinChangerPanel;

#include "../UI/stdui.h"
#include "../atgui.h"
#include "../settings.h"
#include "../Hooks/hooks.h"
#include "../util_items.h"

class SkinChangerPanel : public Panel
{
private:
  StackedListBox<ItemDefinitionIndex>* lb_knifetype;
  Button* updateknife_button;

  void update_knife_clicked ();
public:
  SkinChangerPanel (Vector2D position, Vector2D size);
};
