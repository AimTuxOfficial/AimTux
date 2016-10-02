#ifndef __WINDOW_H_
#define __WINDOW_H_

#include "component.h"
#include "panel.h"

class Window : public Panel
{
private:
	std::string title;
	Component* titleBar;
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