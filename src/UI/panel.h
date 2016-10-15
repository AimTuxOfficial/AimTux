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
	Color backGroundColor = Color (0, 0, 0, 0);
	
	Panel ();
	Panel (Vector2D position);
	Panel (Vector2D position, Vector2D size);
	Panel (Vector2D position, Vector2D size, Color backgroundColor);
	
	virtual void AddComponent (Component* component)
	{
		childComponents.push_back (component);
	}
	virtual void RemoveComponent (Component* component)
	{
		childComponents.erase (std::remove(childComponents.begin(), childComponents.end(), component));
	}
	
	virtual void OnMouseClickStart (PositionContext position);
	virtual void OnMouseClickEnd (PositionContext position);
	virtual void MouseTick (PositionContext position);
	virtual void Draw ();
};

#endif