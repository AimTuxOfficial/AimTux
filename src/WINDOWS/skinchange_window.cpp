#include "skinchange_window.h"

SkinChangerWindow* skinchange_window = nullptr;

SkinChangerWindow::SkinChangerWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, true)
{
  int tab_height = 37;

  knifeskin_panel = new KnifeSkinPanel(LOC (0, tab_height), LOC (size.x, size.y - tab_height));
  weaponskin_panel = new WeaponSkinPanel(LOC (0, tab_height), LOC (size.x, size.y - tab_height));

  AddComponent(knifeskin_panel);
  AddComponent(weaponskin_panel);

  std::vector<TabElement> tabs
	(
		{
			TabElement ("Weapon Skin", weaponskin_panel),
			TabElement ("Knife Skin", knifeskin_panel)
		}
	);

  tabSelector = new TabSelector (LOC (0, 0), LOC (size.x, tab_height), tabs);
	AddComponent (tabSelector);
}
