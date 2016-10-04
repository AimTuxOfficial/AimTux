#include "window.h"
#include "button.h"

/*------------------
	Constructors
------------------*/

int titleBarHeight = 40;


Window::Window (std::string title)
{
	this->title = title;
	
	// Add base components like title bar and main panel
	
	mainPanel = new Panel (Vector2D (0, titleBarHeight), this->size, Color (255, 255, 255, 50));
	this->childComponents.push_back (mainPanel);
	
	titleBar = new TitleBar (this, LOC (0, 0));
	this->childComponents.push_back (titleBar);
	
	
	Button* button = new Button ("Test button", LOC(10, 10), LOC (130, 40));
	mainPanel->AddComponent (button);
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








