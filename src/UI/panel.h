#ifndef __PANEL_H_
#define __PANEL_H_

#include "component.h"
#include <vector>


class Panel : public Component
{
private:
	std::vector<Component*> childComponents;
public:
	void AddComponent (Component* component);
	void RemoveComponent (Component* component);
	virtual void Draw ();
};

#endif