#ifndef __CURSOR_H
#define __CURSOR_H

#include "component.h"

extern bool isMouseDown;

class Cursor : public Component {
public:
	void Draw ();
};

#endif //AIMTUX_CURSOR_H
