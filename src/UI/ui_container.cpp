#include "ui_container.h"

Color Settings::UI::mainColor = Color (255, 100, 100);
Color Settings::UI::bodyColor = Color (20, 20, 20, 190);

bool lastIsMouseDown = false;

bool UI_Container::IsOverlapping (Vector2D position, int index)
{
	int x = position.x;
	int y = position.y;
	
	for (size_t i = windows.size()-1; (int)i != index; i--)
	{
		Window* window = windows[i];
		
		if (window->shown && x >= window->position.x && x <= window->position.x + window->size.x &&
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
	
	Draw::DrawString ("AimTux", LOC (10, 10), Color (215, 215, 215, 190), esp_font);
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
	
	for (size_t i = windows.size ()-1; i >= 0; i--)
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
	
	
	for (std::vector<Window*>::iterator it = window_remove_stack.begin(); it != window_remove_stack.end (); it++)
	{
		windows.erase (std::remove(windows.begin(), windows.end(), *it));
	}
	window_remove_stack.clear ();
	
	for (size_t i = 0; i < windows.size (); i++)
	{
		Window* window = windows[i];
		
		if (!window->IsShown ())
		{
			continue;
		}
		
		window->Input ();
	}

	// Loop through all windows
	for (size_t i = 0; i < windows.size (); i++)
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

	cvar->FindVar("cl_mouseenable")->SetValue (!visible);
}

bool UI_Container::isVisible ()
{
	return visible;
}
