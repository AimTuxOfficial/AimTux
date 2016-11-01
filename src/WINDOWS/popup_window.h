#pragma once

class PopupWindow;

#include "../UI/stdui.h"
#include "../atgui.h"


class PopupWindow : public Window
{
protected:
	Button* bn_cancel;
public:
	PopupWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor);
	void bn_cancel_clicked ();
};

class PopupColorWindow : public PopupWindow
{
protected:
	Color old_color;
	Color* color;
	Button* bn_save;
	
	Slider_INT* sl_r;
	Slider_INT* sl_g;
	Slider_INT* sl_b;
	Slider_INT* sl_a;

public:
	PopupColorWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor, Color* color);
	void bn_cancel_revert_clicked ();
	void bn_save_clicked ();
	void OnShown ();
};
