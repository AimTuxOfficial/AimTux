#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include <functional>
#define MFUNC(a,b) std::bind(a, b)


#include "../color.h"
#include "../pstring.h"
#include "../vector.h"
#include "../draw.h"
#include "../fonts.h"

typedef Vector2D PositionContext;

class Component
{
protected:
	
/*------------------
	Draw Methods
	
	Methods for drawing to the screen restricted to the -
	context of the components bounds (position & size).
	
------------------*/
	
	void Clear (Color color);
	void DrawString (std::wstring text, FONT font, Color color, Vector2D position);
	void DrawCenteredString (std::wstring text, FONT font, Color color, Vector2D position);
	void DrawRectangle (Vector2D start, Vector2D end, Color color);
	void DrawFilledRectangle (Vector2D start, Vector2D end, Color color);
	void DrawLine (Vector2D start, Vector2D end, Color color);
	
	
public:
	
	bool isHovered = false;
	bool isMouseDown = false;
	
	// Events
	std::function<void()> onMouseClickStartEvent;
	std::function<void()> onMouseClickEndEvent;
	std::function<void()> onMouseEnterEvent;
	std::function<void()> onMouseLeaveEvent;
	
	
	PositionContext context = LOC (0,0);
	Vector2D position;
	Vector2D size;
	unsigned int opacity;
	
	Component ()
	{
	}
	
	
	Component (Vector2D position)
	{
		this->position = position;
	}
	
	Component (Vector2D position, Vector2D size) : Component (position)
	{
		this->size = size;
	}
	
	virtual void MouseTick (PositionContext position) { }
	virtual void Draw () { }
	virtual void DoReleaseTree () { }
};

#endif