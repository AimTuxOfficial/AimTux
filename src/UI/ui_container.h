#pragma once

#include "window.h"
#include "cursor.h"
#include <algorithm> // std::remove

class UI_Container
{
private:
	std::vector<Window*> windows;
	Cursor cursor = Cursor();
	bool visible = false;
	std::vector<Window*> window_remove_stack;
public:
	
	void AddWindow (Window* window)
	{
		// Add the window into the vector
		windows.push_back (window);
	}
	
	void RemoveWindow (Window* window)
	{
		// Remove the window from the vector
		//window_remove_stack.push_back (window);
		window_remove_stack.push_back (window);
	}
	
	void Focus (Window* window)
	{
		// Push the window to the top of the stack
		windows.erase (std::remove(windows.begin(), windows.end(), window));
		windows.push_back (window);
	}
	
	void Draw ();
	void Toggle ();
	bool IsOverlapping (Vector2D position, int index);
	bool isVisible ();
};

extern UI_Container* gui;
