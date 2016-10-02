#include "window.h"

/*------------------
	Constructors
------------------*/

int titleBarHeight = 40;


Window::Window (std::string title)
{
	this->title = title;
	
	// Add base components like title bar and main panel
	
	titleBar = new TitleBar (LOC (0, 0));
	this->AddComponent (titleBar);
	
	mainPanel = new Panel (Vector2D (0, titleBarHeight), this->size, Color (255, 255, 255, 50));
	this->AddComponent (mainPanel);
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


Window::Window (std::string title, Vector2D size, Vector2D position, Color color) : Window (title, size, position)
{
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








