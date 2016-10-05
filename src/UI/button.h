#ifndef __BUTTON_H_
#define __BUTTON_H_

#include "component.h"
#include "../settings.h"

class Button : public Component
{
public:
	
	std::function<void()> OnClickedEvent;
	
	std::wstring text = L"button";
	
	void Event_OnMouseClickEnd ()
	{
		if (OnClickedEvent != NULL)
		{
			OnClickedEvent ();
		}
	}
	
	Button (std::string text, Vector2D position, Vector2D size)
	{
		this->position = position;
		this->size = size;
		this->text = std::wstring(text.begin(), text.end ());
		
		onMouseClickEndEvent	= MFUNC (&Button::Event_OnMouseClickEnd, this);
	}
	
	void Draw ()
	{
		Color color = isHovered ? Color (150, 100, 100) : Color (200, 100, 100, 255);
		Clear (color);
		
		DrawCenteredString (text, normal_font, Color (255, 255, 255, 255), LOC (size.x / 2, size.y / 2));
	}
};

class OutlinedButton : public Button
{
public:
	OutlinedButton (std::string text, Vector2D position, Vector2D size)
						: Button (text, position, size) { }
	
	void Draw ()
	{
		Clear (Color (40, 40, 40, 150));
		
		if (isHovered)
		{
			DrawRectangle (LOC (0, 0), size, Settings::UI::titleBarColor);
		}
		
		DrawCenteredString (text, normal_font, Color (255, 255, 255, 255), LOC (size.x / 2, size.y / 2));
	}
};



#endif