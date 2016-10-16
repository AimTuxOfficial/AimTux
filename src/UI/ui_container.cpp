#include "ui_container.h"

bool lastIsMouseDown = false;

bool UI_Container::IsOverlapping (Vector2D position, int index)
{
	int x = position.x;
	int y = position.y;
	
	for (int i = windows.size()-1; i != index; i--)
	{
		Window* window = windows[i];
		
		if (x >= window->position.x && x <= window->position.x + window->size.x &&
				y >= window->position.y && y <= window->position.y + window->size.y)
		{
			return true;
		}
	}
	
	return false;
}

void DrawBanner ()
{
	int width, height;
	engine->GetScreenSize (width, height);
	
	Draw::DrawString ("AimTux", LOC (10, 10), Color (215, 215, 215, 190), esp_font, false);
}

void UI_Container::Draw ()
{
	if (!visible)
	{
		if (!engine->IsInGame ())
		{
			DrawBanner ();
		}
		
		return;
	}
	
	int width, height;
	engine->GetScreenSize (width, height);
	
	Draw::DrawRect (LOC(0, 0), LOC (width, height), Color (0, 0, 0, 20));
	
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
			// Process Click events
			if (input->IsButtonDown (MOUSE_LEFT))
			{
				if (!lastIsMouseDown)
				{
					window->OnMouseClickStart (PositionContext(x, y) - window->position);
				}
			}
			else
			{
				if (lastIsMouseDown)
				{
					window->OnMouseClickEnd (PositionContext(x, y) - window->position);
				}
			}
			
			// Process mouse movement events
			if (!IsOverlapping(PositionContext(x, y), i))
			{
				window->MouseTick (PositionContext(x, y) - window->position);
			}
			else
			{
				window->DoReleaseTree ();
			}
		}
	}
	
	for (int i = 0; i < windows.size (); i++)
	{
		Window* window = windows[i];
		
		if (!window->IsShown ())
		{
			continue;
		}
		
		window->Input ();
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
	
	lastIsMouseDown = input->IsButtonDown (MOUSE_LEFT);
	
	// Draw cursor
	cursor.Draw ();
}

void UI_Container::Toggle ()
{
	visible = !visible;

	engine->ExecuteClientCmd(visible ? "cl_mouseenable 0" : "cl_mouseenable 1");
}







