#include "window.h"

/*------------------
	Constructors
------------------*/

Window::Window (std::string title)
{
	this->title = title;
	
	// Add base components like title bar and main panel
	// ...
}


Window::Window (std::string title, Vector2D size) : Window (title)
{
	this->size = size;
}


Window::Window (std::string title, Vector2D size, Vector2D position) : Window (title, size)
{
	this->position = position;
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








