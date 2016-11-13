#include "slider.h"

void Slider::MouseTick (PositionContext context)
{
	if (isMouseDown)
	{
		*value = ((((float)context.x) / size.x) * (MAX-MIN)) + MIN;
	}
}

void Slider::Draw ()
{
	// Glider = middle bar
	int gliderHeight = size.y / 5;
	int gliderYLoc = (size.y / 2) - (gliderHeight / 2);
	
	DrawFilledRectangle (LOC(0, gliderYLoc), LOC(size.x, gliderYLoc + gliderHeight), background_color);
	
	int dongleWidth = 10;
	
	// donglePosition_px is calculated here and NOT in MouseTick becasue we want the position to be calculated live & when created (0 by default)
	int donglePosition_px = (((float)*value-MIN) / (MAX-MIN)) * size.x;
	
	DrawFilledRectangle (LOC (donglePosition_px - (dongleWidth / 2), 5), LOC (donglePosition_px + dongleWidth / 2, size.y-5), cSettings.UI.mainColor);
	
	pstring _text;

	if (text.length() > 0)
		_text << text << " ";

	_text << (ROUNDF (*value, 100));
	
	DrawCenteredString (_text, normal_font, text_color, LOC (size.x / 2, size.y / 2));
}

void Slider::Input ()
{
	if (isHovered)
	{
		if (input->IsButtonDown (KEY_LEFT))
		{
			*value = MIN;
		}
		else if (input->IsButtonDown (KEY_RIGHT))
		{
			*value = MAX;
		}
	}
}









void Slider_INT::MouseTick (PositionContext context)
{
	if (isMouseDown)
	{
		*value = ((((float)context.x) / size.x) * (MAX-MIN)) + MIN;
	}
}

void Slider_INT::Draw ()
{
	// Glider = middle bar
	int gliderHeight = size.y / 5;
	int gliderYLoc = (size.y / 2) - (gliderHeight / 2);
	
	DrawFilledRectangle (LOC(0, gliderYLoc), LOC(size.x, gliderYLoc + gliderHeight), background_color);
	
	int dongleWidth = 10;
	
	// donglePosition_px is calculated here and NOT in MouseTick becasue we want the position to be calculated live & when created (0 by default)
	int donglePosition_px = (((float)*value-MIN) / (MAX-MIN)) * size.x;
	
	DrawFilledRectangle (LOC (donglePosition_px - (dongleWidth / 2), 5), LOC (donglePosition_px + dongleWidth / 2, size.y-5), cSettings.UI.mainColor);
	
	pstring _text;

	if (text.length() > 0)
		_text << text << " ";

	_text << (ROUNDF (*value, 100));
	
	DrawCenteredString (_text, normal_font, text_color, LOC (size.x / 2, size.y / 2));
}

void Slider_INT::Input ()
{
	if (isHovered)
	{
		if (input->IsButtonDown (KEY_LEFT))
		{
			*value = MIN;
		}
		else if (input->IsButtonDown (KEY_RIGHT))
		{
			*value = MAX;
		}
	}
}