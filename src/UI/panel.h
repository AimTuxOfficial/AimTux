#ifndef __PANEL_H_
#define __PANEL_H_

#include "component.h"
#include <vector>
#include <algorithm>

class Panel : public Component
{
protected:
	std::vector<Component*> childComponents;
public:
	Color backGroundColor;
	void AddComponent (Component* component);
	void RemoveComponent (Component* component);
	virtual void Draw ();
};

#endif