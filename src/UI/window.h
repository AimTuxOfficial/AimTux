#ifndef __WINDOW_H_
#define __WINDOW_H_

#include "component.h"
#include "panel.h"

class TitleBar : public Component
{
public:
	Color backColor = Color (255, 100, 100);
	
	TitleBar (Vector2D position)
	{
		this->position = position;
	}
	
	void Draw ()
	{
		Clear (backColor);
	}
};

class Window : public Panel
{
private:
	std::string title;
	TitleBar* titleBar;
	Panel* mainPanel;
	bool shown;
public:
	Window (std::string title);
	Window (std::string title, Vector2D size);
	Window (std::string title, Vector2D size, Vector2D position);
	Window (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
	void Show ();
	void Hide ();
	bool IsShown ();
};

#endif