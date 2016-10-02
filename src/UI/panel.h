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
	
	Panel ();
	Panel (Vector2D position);
	Panel (Vector2D position, Vector2D size);
	Panel (Vector2D position, Vector2D size, Color backgroundColor);
	
	void AddComponent (Component* component);
	void RemoveComponent (Component* component);
	virtual void Draw ();
};

#endif