#ifndef __TOGGLE_H_
#define __TOGGLE_H_

#include "component.h"
#include "../settings.h"

class ToggleSwitch : public Component
{
public:
	bool* setting;
	std::wstring text = L"toggle switch";
	
	void Event_OnClickEnd ()
	{
		*setting = !*setting;
	}
	
	ToggleSwitch (std::string text, Vector2D position, Vector2D size, bool* setting)
	{
		this->position = position;
		this->size = size;
		this->text = std::wstring(text.begin(), text.end ());
		this->setting = setting;
		
		this->onMouseClickEndEvent = MFUNC (&ToggleSwitch::Event_OnClickEnd, this);
	}
	
	ToggleSwitch (std::string text, Vector2D position, int height, bool* setting)
	{
		this->text = std::wstring(text.begin(), text.end ());
		Vector2D textSize = Draw::GetTextSize (this->text.c_str(), normal_font);
		this->size = LOC (height + 20 + (textSize.x) , height);
		this->position = position;
		this->setting = setting;
		
		this->onMouseClickEndEvent = MFUNC (&ToggleSwitch::Event_OnClickEnd, this);
	}
	
	
	void Draw ()
	{
		Clear (Color (160, 160, 160, (isHovered ? 10 : 5)));
		
		int sep = size.y / 4;
		
		if (!*setting)
		{
			DrawRectangle (LOC (sep, sep), LOC ((size.y / 4) * 3, (size.y / 4) * 3), Settings::UI::titleBarColor);
		}
		else
		{
			DrawRectangle (LOC (sep, sep), LOC ((size.y / 4) * 3, (size.y / 4) * 3), Settings::UI::titleBarColor);
			DrawFilledRectangle (LOC (sep + 2, sep + 2), LOC (((size.y / 4) * 3) - 2, ((size.y / 4) * 3) - 2), Settings::UI::titleBarColor);
		}
		
		Vector2D textSize = Draw::GetTextSize (text.c_str(), normal_font);
		
		DrawString (text, normal_font, Color (255, 255, 255, 200), LOC (size.x-textSize.x-(sep*2), (size.y/2)-(textSize.y/2)));
	}
};


#endif