#pragma once

#include <functional>
#include "../SDK/color.h"
#include "../SDK/vector.h"
#include "../pstring.h"
#include "../draw.h"
#include "../fonts.h"

#define MFUNC(a,b) std::bind(a, b)

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
	void DrawString (std::string text, FONT font, Color color, Vector2D position);
	void DrawCenteredString (std::string text, FONT font, Color color, Vector2D position);
	void DrawRectangle (Vector2D start, Vector2D end, Color color);
	void DrawFilledRectangle (Vector2D start, Vector2D end, Color color);
	void DrawLine (Vector2D start, Vector2D end, Color color);
	void DrawPolygon (Vector2D a, Vector2D b, Vector2D c, Color color);


public:
	bool shown = true;
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

	bool IsShown ()
	{
		return shown;
	}

	void Show ()
	{
		shown = true;
	}

	void Hide ()
	{
		shown = false;
	}

	virtual void OnMouseClickStart (PositionContext mouseContext) { }
	virtual void OnMouseClickEnd (PositionContext mouseContext) { }
	virtual void Input () { }
	virtual void MouseTick (PositionContext position) { }
	virtual void Draw () { }
	virtual void DoReleaseTree () { }
};
