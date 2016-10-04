#include "panel.h"


Panel::Panel ()
{
}


Panel::Panel (Vector2D position) : Panel ()
{
	this->position = position;
}

Panel::Panel (Vector2D position, Vector2D size) : Panel (position)
{
	this->size = size;
}


Panel::Panel (Vector2D position, Vector2D size, Color backgroundColor) : Panel (position, size)
{
	this->backGroundColor = backgroundColor;
}

void Panel::Draw ()
{
	this->Clear (backGroundColor);
	
	
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		// Update the childs context
		childComponent->context = this->context + childComponent->position;
		
		// Draw the component
		childComponent->Draw ();
	}
}

void Panel::DoReleaseTree ()
{
	this->isHovered = false;
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		childComponent->isHovered = false;
		
		if (childComponent->onMouseLeaveEvent != NULL)
		{
			childComponent->onMouseLeaveEvent ();
		}
		
		childComponent->DoReleaseTree ();
	}
}

void Panel::MouseTick (PositionContext mouseContext)
{
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		int x = mouseContext.x;
		int y = mouseContext.y;
		
		if	(
				x >= childComponent->position.x && x <= childComponent->position.x + childComponent->size.x &&
				y >= childComponent->position.y && y <= childComponent->position.y + childComponent->size.y
			)
		{
			if (!childComponent->isHovered)
			{
				childComponent->isHovered = true;
				if (childComponent->onMouseEnterEvent != NULL)
				{
					childComponent->onMouseEnterEvent();
				}
			}
			
			
			if (!childComponent->isMouseDown && input->IsButtonDown (MOUSE_LEFT))
			{
				childComponent->isMouseDown = true;
				if (childComponent->onMouseClickStartEvent != NULL)
				{
					childComponent->onMouseClickStartEvent ();
				}
			}
			
			if (childComponent->isMouseDown && !input->IsButtonDown (MOUSE_LEFT))
			{
				childComponent->isMouseDown = false;
				if (childComponent->onMouseClickEndEvent != NULL)
				{
					childComponent->onMouseClickEndEvent ();
				}
			}
			
			childComponent->MouseTick (mouseContext - childComponent->position);
		}
		else
		{
			if (childComponent->isHovered)
			{
				childComponent->isHovered = false;
				if (childComponent->onMouseLeaveEvent != NULL)
				{
					childComponent->onMouseLeaveEvent();
				}
			}
		}
	}
}




