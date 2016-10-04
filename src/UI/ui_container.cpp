#include "ui_container.h"

void UI_Container::Draw ()
{
	if (!visible)
	{
		return;
	}
	
	for (int i = windows.size ()-1; i >= 0; i--)
	{
		Window* window = windows[i];
		
		if (!window->IsShown ())
		{
			continue;
		}
		
		int x, y;
		input->GetCursorPosition(&x, &y);
		
		if	(
				x >= window->position.x && x <= window->position.x + window->size.x &&
				y >= window->position.y && y <= window->position.y + window->size.y
			)
		{
			window->MouseTick (PositionContext(x, y) - window->position);
		}
	}

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

void UI_Container::Toggle ()
{
	visible = !visible;

	engine->ExecuteClientCmd(visible ? "cl_mouseenable 0" : "cl_mouseenable 1");
}







