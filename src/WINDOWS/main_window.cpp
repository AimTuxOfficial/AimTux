#include "main_window.h"

MainWindow* main_window = nullptr;

MainWindow::MainWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, true)
{

	int tab_height = 37;

	pl_aimbot = new AimbotPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_triggerbot = new TriggerbotPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_visuals = new VisualsPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_hvh = new HVHPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_misc = new MiscPanel (LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_skin = new SkinChangerPanel(LOC (0, tab_height), LOC (size.x, size.y - tab_height));
	pl_config = new ConfigPanel(LOC (0, tab_height), LOC (size.x, size.y - tab_height));


	AddComponent (pl_aimbot);
	AddComponent (pl_triggerbot);
	AddComponent (pl_visuals);
	AddComponent (pl_hvh);
	AddComponent (pl_misc);
	AddComponent (pl_skin);
	AddComponent (pl_config);

	std::vector<TabElement> tabs
	(
		{
			TabElement ("Aimbot", pl_aimbot),
			TabElement ("Triggerbot", pl_triggerbot),
			TabElement ("Visuals", pl_visuals),
			TabElement ("HVH", pl_hvh),
			TabElement ("Misc", pl_misc),
			TabElement ("Skin Changer", pl_skin),
			TabElement ("Config", pl_config)
			
		}
	);

	tabSelector = new TabSelector (LOC (0, 0), LOC (size.x, tab_height), tabs);
	AddComponent (tabSelector);

	Show ();
}
