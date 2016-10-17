#ifndef __BANNER_H_
#define __BANNER_H_

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
		this->size = Vector2D (width, text_size.y);
	}
	
	void Draw ()
	{
		DrawLine (Vector2D (0, size.y / 2), Vector2D ((size.x / 2) - (text_size.x / 2) - BANNER_TEXT_GAP, size.y / 2), Color (255, 255, 255, 120));
		DrawLine (Vector2D ((size.x / 2) + (text_size.x / 2) + BANNER_TEXT_GAP, size.y / 2), Vector2D (size.x, size.y / 2), Color (255, 255, 255, 170));
		
		DrawCenteredString (text, normal_font, Color (255, 255, 255, 255), Vector2D (size.x / 2, size.y / 2));
	}
};


#endif