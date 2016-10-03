#ifndef __BUTTON_H_
#define __BUTTON_H_

#include "component.h"

class Button : public Component
{
public:
	
	std::function<void()> OnClickedEvent;
	
	std::string text;
	Color backGroundColor;
	Color foreGroundColor;
	
	Button (Vector2D position, Vector2D size)
	{
		this->position = position;
		this->size = size;
	}
	
	void Draw ()
	{
		Color color = isHovered ? Color (100, 255, 100) : Color (100, 100, 255);
		Clear (color);
		
		DrawCenteredString (std::wstring (L"test"), normal_font, Color (255, 255, 255), LOC (size.x / 2, size.y / 2));
	}
	
	void MouseMove (PositionContext mouseContext)
	{
		PRINT ("Hello World");
	}
};



#endif