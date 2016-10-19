#pragma once

#include "component.h"

extern bool isMouseDown;

class Cursor : public Component {
public:
	void Draw ();
};