#ifndef __WINDOW_H_
#define __WINDOW_H_

class Window;
class TitleBar;

#include "component.h"
#include "panel.h"
#include "ui_container.h"

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
	
	void Toggle ()
	{
		shown = !shown;
	}
	
	void Draw ();
};

class TitleBar : public Component
{
private:
	Vector2D mouseClickStartPosition = LOC (0, 0);
public:
	Window* parentWindow;
	
	Color foreColor = Color (255, 255, 255);
	
	void OnMouseClickStart ();
	
	TitleBar (Window* window, Vector2D position)
	{
		this->position = position;
		this->parentWindow = window;
		
		onMouseClickStartEvent = MFUNC (&TitleBar::OnMouseClickStart, this);
	}
	
	void Draw ();
};

#endif