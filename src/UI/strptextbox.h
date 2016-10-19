#ifndef __STRPTEXTBOX_H_
#define __STRPTEXTBOX_H_

#include "component.h"
#include "../settings.h"
#include "../util.h"
#include <algorithm>

class StrPTextBox : public Component
{
protected:
	Color text_color = Color (255, 255, 255, 200);
	Color background_color = Color (160, 160, 160, 5);
private:
	std::vector<ButtonCode_t> lastPressedKeys;
	Vector2D font_size;
	
	bool s_showCaret = false;
	int s_caret_stamp;
public:
	
    std::string* text;
	std::string shadow_text = "textbox";
	
	StrPTextBox (std::string shadow_text, std::string* textref, Vector2D position, Vector2D size)
	{
		this->position = position;
		this->size = size;
		this->shadow_text = shadow_text;
		this->text = textref;
		
		// Get the width if the monospaced font
		font_size = Draw::GetTextSize ("j", mono_font);
		
		// set the default caret_stamp to the current tick_count
		s_caret_stamp = globalvars->tickcount;
	}
	
	void Draw ()
	{
		Clear (background_color);
		
		if (isHovered)
		{
			DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
		}
		
		
		int text_max_fit = (size.x-20) / font_size.x;
		
		const char* sectioned_text = (text->size() > text_max_fit ? &text->c_str()[text->size() - text_max_fit] : text->c_str());
		
		int sectioned_text_size = strlen(sectioned_text);
		
		DrawString (sectioned_text, mono_font, text_color, LOC (10, (size.y / 2) - (font_size.y / 2)));
		
		int current_tick = globalvars->tickcount;
		
		if (current_tick > s_caret_stamp + 40)
		{
			s_caret_stamp = current_tick;
			s_showCaret = !s_showCaret;
		}
		
		// Draw caret
		if (s_showCaret && isHovered)
		{
			DrawFilledRectangle (LOC (12 + (sectioned_text_size * font_size.x), (size.y / 4)), LOC (14 + (sectioned_text_size * font_size.x), (size.y / 4) * 3), text_color);
		}
	}
	
	bool GetPressedKeys (std::vector<ButtonCode_t>& pressedKeys)
	{
		bool _isKeyPressed = false;
		
		for (int i = KEY_0; i <= KEY_RIGHT; i++)
		{
			ButtonCode_t key = (ButtonCode_t)i;
			
			if (input->IsButtonDown (key))
			{
				_isKeyPressed = true;
				pressedKeys.push_back (key);
			}
		}
		
		return _isKeyPressed;
	}

	void Input ()
	{
		if (!isHovered)
		{
			return;
		}
		
		std::vector<ButtonCode_t> pressedKeys;
		bool isKeyPressed = GetPressedKeys (pressedKeys);
		bool shift = input->IsButtonDown (KEY_LSHIFT) || input->IsButtonDown (KEY_RSHIFT);
		
		for (int i = 0; i < pressedKeys.size(); i++)
		{
			ButtonCode_t key = (ButtonCode_t)pressedKeys[i];
			
			if (std::find(lastPressedKeys.begin(), lastPressedKeys.end(), key) != lastPressedKeys.end() || key > KEY_EQUAL)
			{
				continue;
			}
			
			char character = Util::GetButtonString(key);
			
			if (shift)
			{
				character = Util::GetUpperValueOf(key);
			}
			
			text->operator+=(character);
		}
		
		if (text->size() > 0 &&
			std::find(pressedKeys.begin(), pressedKeys.end(), KEY_BACKSPACE) != pressedKeys.end() &&
			std::find(lastPressedKeys.begin(), lastPressedKeys.end(), KEY_BACKSPACE) == lastPressedKeys.end()
			)
		{
			text->pop_back ();
		}
		
		if (text->size() > 0 &&
			std::find(pressedKeys.begin(), pressedKeys.end(), KEY_SPACE) != pressedKeys.end() &&
			std::find(lastPressedKeys.begin(), lastPressedKeys.end(), KEY_SPACE) == lastPressedKeys.end()
			)
		{
			text->operator+=(" ");
		}
		
		lastPressedKeys = pressedKeys;
	}
};

#endif
