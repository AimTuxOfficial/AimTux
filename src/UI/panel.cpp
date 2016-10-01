#include "panel.h"


void Panel::AddComponent (Component* component)
{
	childComponents.push_back (component);
}

void Panel::RemoveComponent (Component* component)
{
	childComponents.erase (std::remove(childComponents.begin(), childComponents.end(), component));
}

void Panel::Draw ()
{
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		childComponent->Draw ();
	}
}