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

// Push the
void Panel::PushTop (Component* component)
{
	childComponents.erase(std::remove(childComponents.begin(), childComponents.end(), component));
	childComponents.push_back (component);
}

void Panel::Draw ()
{
	if (shown)
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
}

void Panel::OnMouseClickStart (PositionContext mouseContext)
{
	for (int i = childComponents.size()-1; i >= 0; i--)
	{
		Component* childComponent = childComponents[i];

		int x = mouseContext.x;
		int y = mouseContext.y;

		if	(childComponent->shown && x >= childComponent->position.x && x <= childComponent->position.x + childComponent->size.x &&
				y >= childComponent->position.y && y <= childComponent->position.y + childComponent->size.y)
		{
			// Push component to the top of the stack

			PushTop (childComponent);
			

			childComponent->OnMouseClickStart (mouseContext - childComponent->position);

			childComponent->isMouseDown = true;

			if (childComponent->onMouseClickStartEvent != NULL)
			{
				childComponent->onMouseClickStartEvent ();
			}
			return;
		}
	}
}

void Panel::OnMouseClickEnd (PositionContext mouseContext)
{
	for (int i = childComponents.size()-1; i >= 0; i--)
	{
		Component* childComponent = childComponents[i];

		int x = mouseContext.x;
		int y = mouseContext.y;

		if	(childComponent->shown && x >= childComponent->position.x && x <= childComponent->position.x + childComponent->size.x &&
				y >= childComponent->position.y && y <= childComponent->position.y + childComponent->size.y)
		{

			// Push component to the top of the stack
			
			PushTop (childComponent);
			

			childComponent->OnMouseClickEnd (mouseContext - childComponent->position);

			childComponent->isMouseDown = false;

			if (childComponent->onMouseClickEndEvent != NULL)
			{
				childComponent->onMouseClickEndEvent ();
			}
			return;
		}
	}
}

void Panel::Input ()
{
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		childComponent->Input ();
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
				childComponent->shown && x >= childComponent->position.x && x <= childComponent->position.x + childComponent->size.x &&
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

			childComponent->MouseTick (mouseContext - childComponent->position);
		}
		else
		{
			if (childComponent->isHovered)
			{
				childComponent->isHovered = false;
				childComponent->isMouseDown = false;
				if (childComponent->onMouseLeaveEvent != NULL)
				{
					childComponent->onMouseLeaveEvent();
				}
			}
		}
	}
}
