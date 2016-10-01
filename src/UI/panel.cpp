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
	this->Clear (Color(0, 0, 0));
	
	
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		// Update the childs context
		childComponent->context = this->context + childComponent->position;
		
		// Draw the component
		childComponent->Draw ();
	}
}