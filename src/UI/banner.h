#pragma once

#include "component.h"
#include "../settings.h"

#define BANNER_TEXT_GAP 10

class Banner : public Component
{
public:
	
	std::function<void()> OnClickedEvent;
	Vector2D text_size;
	std::string text = "button";
	
	Banner (std::string text, Vector2D position, int width)
	{
		this->position = position;
		this->text = text;
		text_size = Draw::GetTextSize (this->text.c_str(), normal_font);
		this->size = LOC (width, text_size.y);
	}
	
	void Draw ()
	{
		DrawLine (LOC (0, size.y / 2), LOC ((size.x / 2) - (text_size.x / 2) - BANNER_TEXT_GAP, size.y / 2), Color (255, 255, 255, 120));
		DrawLine (LOC ((size.x / 2) + (text_size.x / 2) + BANNER_TEXT_GAP, size.y / 2), LOC (size.x, size.y / 2), Color (255, 255, 255, 170));
		
		DrawCenteredString (text, normal_font, Color (255, 255, 255, 255), LOC (size.x / 2, size.y / 2));
	}
};