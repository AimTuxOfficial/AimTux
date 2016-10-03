#ifndef __WINDOW_H_
#define __WINDOW_H_

#include "component.h"
#include "panel.h"

class TitleBar;

class Window : public Panel
{
private:
	TitleBar* titleBar;
	Panel* mainPanel;
	bool shown;
public:
	std::string title;
	Window (std::string title);
	Window (std::string title, Vector2D size);
	Window (std::string title, Vector2D size, Vector2D position);
	Window (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
	void Show ();
	void Hide ();
	bool IsShown ();
	
	
	void AddComponent (Component* component)
	{
		mainPanel->AddComponent (component);
	}
	
	void RemoveComponent (Component* component)
	{
		mainPanel->RemoveComponent (component);
	}
};


class TitleBar : public Component
{
private:
	Vector2D mouseClickStartPosition = LOC (0, 0);
public:
	Window* parentWindow;
	
	Color backColor = Color (255, 100, 100);
	Color foreColor = Color (255, 255, 255);
	
	void OnMouseClickStart ()
	{
		int x, y;
		input->GetCursorPosition(&x, &y);
		
		mouseClickStartPosition = LOC (x, y) - parentWindow->position;
	}
	
	void MouseTick (PositionContext position)
	{
		if (isMouseDown)
		{
			int x, y;
			input->GetCursorPosition(&x, &y);
			
			Vector2D newPos = LOC (x, y) - mouseClickStartPosition;
			
			parentWindow->position = newPos;
		}
	}
	
	
	TitleBar (Window* window, Vector2D position)
	{
		this->position = position;
		this->parentWindow = window;
		
		onMouseClickStartEvent = MFUNC (&TitleBar::OnMouseClickStart, this);
	}
	
	void Draw ()
	{
		Clear (backColor);
		DrawCenteredString (std::wstring (parentWindow->title.begin(), parentWindow->title.end()), title_font, foreColor, LOC (size.x / 2, size.y / 2));
	}
};

#endif