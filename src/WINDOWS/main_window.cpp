#include "main_window.h"

MainWindow* main_window = nullptr;

MainWindow::MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, false)
{
	
	int tab_height = 60;
	
	pl_aimbot = new AimbotPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_triggerbot = new TriggerbotPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_visuals = new ESPPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_hvh = new HVHPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_misc = new MiscPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	
	
	AddComponent (pl_aimbot);
	AddComponent (pl_triggerbot);
	AddComponent (pl_visuals);
	AddComponent (pl_hvh);
	AddComponent (pl_misc);
	
	std::vector<TabElement> tabs
	(
		{
			TabElement ("Aimbot", pl_aimbot),
			TabElement ("Triggerbot", pl_triggerbot),
			TabElement ("Visuals", pl_visuals),
			TabElement ("HVH", pl_hvh),
			TabElement ("Misc", pl_misc)
		}
	);
	
	tabSelector = new TabSelector (LOC (0, 0), LOC (size.x, tab_height), tabs);
	AddComponent (tabSelector);
	
	Show ();
}
