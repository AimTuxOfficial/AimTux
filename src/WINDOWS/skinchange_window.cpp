#include "skinchange_window.h"

SkinChangeWindow* skinchange_window = nullptr;

SkinChangeWindow::SkinChangeWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, true)
{

	int tab_height = 46;

	pl_knife = new SkinChangerPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));

	AddComponent (pl_knife);

	std::vector<TabElement> tabs
	(
		{
			TabElement ("Knife Changer (Alpha)", pl_knife)
		}
	);

	tabSelector = new TabSelector (LOC (0, 0), LOC (size.x, tab_height), tabs);
	AddComponent (tabSelector);

	Show ();
}
