#ifndef __UI_CONTAINER_H_
#define __UI_CONTAINER_H_

#include "window.h"
#include "cursor.h"
#include <algorithm> // std::remove

class UI_Container
{
private:
	std::vector<Window*> windows;
	Cursor cursor = Cursor();
	bool visible = false;
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
		for (int i = 0; i < windows.size(); i++)
		{
			Window* window = windows[i];
			
			int x, y;
			input->GetCursorPosition(&x, &y);
			
			if	(
					x >= window->position.x && x <= window->position.x + window->size.x &&
					y >= window->position.y && y <= window->position.y + window->size.y
				)
			{
				window->MouseMove (PositionContext(x, y) - window->position);
			}
		}
		
		if (!visible)
			return;

		// Loop through all windows
		for (int i = 0; i < windows.size (); i++)
		{
			Window* window = windows[i];
			
			// If the window is shown (visible), draw it
			if (window->IsShown ())
			{
				window->context = window->position;
				window->Draw ();
			}
		}

		// Draw cursor
		cursor.Draw ();
	}
	
	void Toggle ()
	{
		visible = !visible;

		engine->ExecuteClientCmd(visible ? "cl_mouseenable 0" : "cl_mouseenable 1");
	}
};

extern UI_Container* gui;

#endif