#pragma once

class PopupWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class PopupWindow : public Window
{
private:
	Button* bn_cancel;
public:
	PopupWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
	void bn_cancel_clicked ();
};
