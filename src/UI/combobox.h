#pragma once

#include "component.h"
#include "button.h"
#include "../settings.h"

#define CB_ELEMENT_HEIGHT 30
#define CB_ELEMENT_SEPARATOR_WIDTH 2

struct CB_Element
{
	std::string name;
	unsigned int value;

	CB_Element (std::string name, unsigned int value)
	{
		this->name = name;
		this->value = value;
	}
};

template<typename T>
class CB_Button : public Button
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color background_color = Color (160, 160, 160, 7);
	Color background_color_hovered = Color (160, 160, 160, 12);
public:
	CB_Element* element;
	bool* open;
	T* setting;

	void Event_OnClickStart ()
	{
		clickStarted = true;
	}

	void Event_OnClickEnd ()
	{
		if(clickStarted)
		{
			*static_cast<unsigned int*>((void*)setting) = element->value;
			*open = false;
		}
	}

	void Event_OnMouseLeave ()
	{
		clickStarted = false;
	}

	CB_Button (std::string text, Vector2D position, Vector2D size, T* setting, CB_Element* element, bool* open)
		: Button (text, position, size)
	{
		this->element = element;
		this->setting = setting;
		this->open = open;
		this->onMouseClickEndEvent		= MFUNC (&CB_Button::Event_OnClickEnd, this);
		this->onMouseClickStartEvent	= MFUNC (&CB_Button::Event_OnClickStart, this);
		this->onMouseLeaveEvent				= MFUNC (&CB_Button::Event_OnMouseLeave, this);
	}

	void Draw ()
	{
		//Clear (isHovered ? background_color_hovered : background_color);
		DrawFilledRectangle (LOC (0, 10), LOC(size.x, size.y), background_color);

		if (*static_cast<unsigned int*>((void*)setting) == element->value)
		{
			DrawRectangle (LOC (0, 10), size, cSettings.UI.mainColor);
		}

		DrawCenteredString (text, normal_font, text_color, LOC (size.x / 2, (size.y / 2) + 5));
	}
};



class ComboBoxButton : public Button
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color hovered_outline_color = Color (200, 200, 200, 20);
	Color background_color = Color (40, 40, 40, 150);
public:
	bool* open;

	void Event_OnClickStart ()
	{
		clickStarted = true;
	}

	void Event_OnClickEnd ()
	{
		if(clickStarted)
			*open = !*open;
	}

	void Event_OnMouseLeave ()
	{
		clickStarted = false;
	}

	ComboBoxButton (std::string text, Vector2D position, Vector2D size, bool* open)
						: Button (text, position, size)
	{
		this->open = open;
		this->onMouseClickEndEvent		= MFUNC (&ComboBoxButton::Event_OnClickEnd, this);
		this->onMouseClickStartEvent	= MFUNC (&ComboBoxButton::Event_OnClickStart, this);
		this->onMouseLeaveEvent				= MFUNC (&ComboBoxButton::Event_OnMouseLeave, this);
	}

	void Draw ()
	{
		Clear (background_color);

		DrawRectangle (LOC(4, 4), LOC(size.x - 4, size.y - 4), cSettings.UI.mainColor);

		if (*open)
		{
		//	DrawRectangle (position, LOC(25, 25), Settings::UI::mainColor);
		//	DrawRectangle (LOC(size.x - 25, 5), LOC(size.x - 5, 25), Settings::UI::mainColor);
			DrawFilledRectangle (LOC(6, 6), LOC(size.x - 6, size.y - 6), cSettings.UI.mainColor);
		}
		else if (isHovered)
		{
		//	DrawRectangle (position, LOC(25, 25), hovered_outline_color);
			DrawFilledRectangle (LOC(6, 6), LOC(size.x - 6, size.y - 6), cSettings.UI.mainColor);
		}

		//DrawRectangle (LOC(size.x - 25, 5), LOC(size.x - 5, 25), Settings::UI::mainColor);
		//DrawCenteredString (text, normal_font, text_color, LOC (size.x / 2, size.y / 2));
	}
};

template<typename E>
class ComboBoxToggle : public Panel
{
protected:
	Color text_color = Color (255, 255, 255, 200);
	Color background_color = Color (160, 160, 160, 5);
	Color background_color_hovered = Color (160, 160, 160, 10);
public:
	bool clickStarted = false;
	std::string text = "ComboBox";
	bool* open;
	std::vector<CB_Element> elements;
	E* setting;


	void Event_OnClickStart ()
	{
		clickStarted = true;
	}

	void Event_OnClickEnd ()
	{
		if(clickStarted){
			for (int i = 0; i < elements.size(); i++)
			{
					CB_Element* element = &this->elements[i];
					if (*setting == element->value)
						this->text = element->name;
			}
		}
	}

	void Event_OnMouseLeave ()
	{
		clickStarted = false;
	}

	ComboBoxToggle<E> (std::string text, Vector2D position, int width, int elements_x, E* setting, std::vector<CB_Element> elements, bool* open)
	{
		this->position = position;
		this->text = text;
		this->open = open;
		this->elements = elements;
		this->setting = setting;

		this->onMouseClickEndEvent		= MFUNC (&ComboBoxToggle::Event_OnClickEnd, this);
		this->onMouseClickStartEvent	= MFUNC (&ComboBoxToggle::Event_OnClickStart, this);
		this->onMouseLeaveEvent			= MFUNC (&ComboBoxToggle::Event_OnMouseLeave, this);

		int elementWidth = (width / elements_x);

		int x = 0, y = 0;
		for (int i = 0; i < elements.size(); i++)
		{
			if (x == elements_x)
			{
				y++;
				x = 0;
			}

			CB_Element* element = &this->elements[i];

			CB_Button<E>* new_button = new CB_Button<E> (

				element->name,
				LOC ((x * elementWidth) + 3, (y * CB_ELEMENT_HEIGHT + 20)),
				LOC (elementWidth - 6, CB_ELEMENT_HEIGHT + 5),
				this->setting,
				element,
				open
				);
			AddComponent (new_button);
			if (*setting == element->value)
				this->text = element->name;
			x++;
		}

		this->size = Vector2D (width + 6, ((((y+1) + CB_ELEMENT_HEIGHT) * elements.size() + 14)));
	}

	//ComboBoxToggle (std::string text, Vector2D position, int height, bool* open)
//		: ComboBoxToggle (text, position, LOC (height + 25 + Draw::GetTextSize (text.c_str(), normal_font).x, height), open) { }
	//ComboBoxButton (std::string text, Vector2D position, Vector2D size, bool* open)


	void Draw ()
	{
		//Clear (isHovered ? background_color_hovered : background_color);

		int sep = size.y / 4;

		if (*open)
		{
			DrawFilledRectangle (LOC(0, 0), LOC(size.x - 6, size.y), background_color);
			DrawRectangle (LOC(0, 0), LOC(size.x - 6, size.y), background_color);
			Panel::Draw();
		}
		else
		{
	//		DrawRectangle (LOC(size.x - 25, 5), LOC(size.x - 5, 25), Settings::UI::mainColor);
	//		DrawFilledRectangle (LOC((size.x - 25) + 2, 5 + 2), LOC((size.x - 5) -2, 25 - 2), Settings::UI::mainColor);
				DrawFilledRectangle (LOC(0, 0), LOC(size.x - 6, 30), background_color);
		}
		//Vector2D textSize = Draw::GetTextSize (text.c_str(), normal_font);
		DrawCenteredString (text, normal_font, text_color, LOC (size.x / 2 - 6, 15));
	}
};
