#include "window.h"
#include "button.h"
#include "../settings.h"

Color Settings::UI::mainColor = Color (255, 100, 100);
Color Settings::UI::bodyColor = Color (20, 20, 20, 190);


/*------------------
	Constructors
------------------*/

int titleBarHeight = 40;


Window::Window (std::string title)
{
	this->title = title;
	
	// Add base components like title bar and main panel
	
	mainPanel = new Panel (Vector2D (0, titleBarHeight), this->size, Color (20, 20, 20, 190));
	this->childComponents.push_back (mainPanel);
	
	titleBar = new TitleBar (this, LOC (0, 0));
	this->childComponents.push_back (titleBar);
}


Window::Window (std::string title, Vector2D size) : Window (title)
{
	this->size = size;
	
	this->mainPanel->size = this->size - LOC (0, titleBarHeight);
	this->titleBar->size = LOC (size.x, titleBarHeight);
}


Window::Window (std::string title, Vector2D size, Vector2D position) : Window (title, size)
{
	this->position = position;
}


Window::Window (std::string title, Vector2D size, Vector2D position, Color color, bool draggable) : Window (title, size, position)
{
	this->draggable = draggable;
	this->backGroundColor = color;
}



/*----------------------
	Member functions
----------------------*/


void Window::Show ()
{
	shown = true;
}


void Window::Hide ()
{
	shown = false;
}


bool Window::IsShown ()
{
	return this->shown;
}


void Window::Draw ()
{
	Panel::Draw ();
	
	DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
}



/*--------------
	TitleBar	
--------------*/

void TitleBar::OnMouseClickStart (PositionContext mouseContext)
{
	if (parentWindow->draggable)
	{
		_isDown = true;
		
		int x, y;
		input->GetCursorPosition(&x, &y);
		
		mouseClickStartPosition = LOC (x, y) - parentWindow->position;
		
		gui->Focus (parentWindow);
	}
}

void TitleBar::OnMouseClickEnd (PositionContext mouseContext)
{
	_isDown = false;
}

void TitleBar::Draw ()
{
	if (parentWindow->draggable)
	{
		int x, y;
		input->GetCursorPosition(&x, &y);
		if (input->IsButtonDown (MOUSE_LEFT) && _isDown)
		{
			Vector2D newPos = LOC (x, y) - mouseClickStartPosition;
			
			parentWindow->position = newPos;
		}
	}
	
	Clear (Settings::UI::mainColor);
	DrawCenteredString (parentWindow->title.c_str(), title_font, foreColor, LOC (size.x / 2, size.y / 2));
}
