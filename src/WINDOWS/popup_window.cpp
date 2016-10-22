#include "popup_window.h"

PopupWindow::PopupWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, true)
{
	bn_cancel = new OutlinedButton ("Cancel", LOC (10, (size.y - (80+10))), LOC ((size.x / 2) - (20), 35));
	bn_cancel->OnClickedEvent = MFUNC (&PopupWindow::bn_cancel_clicked, this);
	AddComponent (bn_cancel);
	
	Hide ();
}

void PopupWindow::bn_cancel_clicked ()
{
	this->Destroy ();
}
