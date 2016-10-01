#ifndef __UI_CONTAINER_H_
#define __UI_CONTAINER_H_

#include "window.h"
#include <algorithm> // std::remove

class UI_Container
{
private:
	std::vector<Window*> windows;
	bool visible;
public:
	
	void AddWindow (Window* window)
	{
		// Add the window into the vector
		windows.push_back (window);
	}
	
	void RemoveWindow (Window* window)
	{
		// Remove the window from the vector
		windows.erase (std::remove(windows.begin(), windows.end(), window));
	}
	
	void Draw ()
	{
		// Loop through all windows
		for (int i = 0; i < windows.size (); i++)
		{
			Window* window = windows[i];
			
			// If the window is shown (visible), draw it
			if (window->IsShown ())
			{
				window->Draw ();
			}
		}
	}
	
	void Toggle ()
	{
		visible = !visible;

		engine->ExecuteClientCmd(visible ? "cl_mouseenable 0" : "cl_mouseenable 1");
	}
};

extern UI_Container* gui;

#endif