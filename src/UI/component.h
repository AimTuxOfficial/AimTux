#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include "panel.h"

class Component
{
public:
	unsigned int opacity;
	virtual void Draw ();
};

#endif