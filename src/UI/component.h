#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include "../color.h"
#include "../pstring.h"
#include "../vector.h"

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
	void DrawString (std::string text, Vector2D position);
	void DrawRectangle (Vector2D start, Vector2D end, Color color);
	void DrawFilledRectangle (Vector2D start, Vector2D end, Color color);
	void DrawLine (Vector2D start, Vector2D end, Color color);
	
	
public:
	PositionContext context;
	Vector2D position;
	Vector2D size;
	unsigned int opacity;
	virtual void Draw () { }
};

#endif