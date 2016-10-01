#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include "../color.h"
#include "../pstring.h"
#include "../vector.h"

class Component
{
public:
	Vector2D position;
	Vector2D size;
	unsigned int opacity;
	virtual void Draw ();
};

#endif