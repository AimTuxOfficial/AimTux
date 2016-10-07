#include "slider.h"

void Slider::MouseTick (PositionContext context)
{
	if (isMouseDown)
	{
		*value = (((float)context.x) / size.x) * MAX;
	}
}

void Slider::Draw ()
{
	// Glider = middle bar
	int gliderHeight = size.y / 5;
	int gliderYLoc = (size.y / 2) - (gliderHeight / 2);
	
	DrawFilledRectangle (LOC(0, gliderYLoc), LOC(size.x, gliderYLoc + gliderHeight), Color (160, 160, 160, 80));
	
	int dongleWidth = 10;
	
	// donglePosition_px is calculated here and NOT in MouseTick becasue we want the position to be calculated live & when created (0 by default)
	int donglePosition_px = (((float)*value) / MAX) * size.x;
	
	DrawFilledRectangle (LOC (donglePosition_px - (dongleWidth / 2), 5), LOC (donglePosition_px + dongleWidth / 2, size.y-5), Settings::UI::mainColor);
	
	pstring _text;
	_text << text << " " << (ROUNDF (*value, 100));
	
	DrawCenteredString (std::wstring(_text.begin(), _text.end()), normal_font, Color (255, 255, 255, 255), LOC (size.x / 2, size.y / 2));
}