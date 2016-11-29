#pragma once

#include "component.h"
#include "button.h"
#include "../settings.h"

#define CB_ELEMENT_HEIGHT 30
#define CB_ELEMENT_SEPARATOR_WIDTH 10

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
	Color background_color = Color (35, 35, 45, 60);
	Color background_color_hovered = Color (35, 35, 45, 100);
public:
	CB_Element* element;
	bool open;
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
			open = false;
		}
	}

	void Event_OnMouseLeave ()
	{
		clickStarted = false;
	}

	CB_Button (std::string text, Vector2D position, Vector2D size, T* setting, CB_Element* element, bool open)
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
		Clear (isHovered ? background_color_hovered : background_color);

		if (*static_cast<unsigned int*>((void*)setting) == element->value)
		{
			DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
		}

		DrawCenteredString (text, normal_font, text_color, LOC (size.x / 2, size.y / 2));
	}
};

template<typename E>
class ComboBox : public Panel
{
protected:
	Color text_color = Color (255, 255, 255, 200);
	Color background_color = Color (25, 25, 35, 250);
	Color background_color_hovered = Color (45, 45, 55, 35);
	Color background_color_closed = Color (45, 45, 55, 25);
public:
	bool clickStarted = false;
	std::string text = "ComboBox";
	bool open;
	int width;
	std::vector<CB_Element> elements;
	E* setting;


	void Event_OnClickStart ()
	{
		clickStarted = true;
	}

	void Event_OnClickEnd ()
	{
		if(clickStarted){
			open = !open;
			UpdateSize(this->width, elements.size());
		}
	}

	void Event_OnMouseLeave ()
	{
		clickStarted = false;
	}

	ComboBox<E> (std::string text, Vector2D position, int width, E* setting, std::vector<CB_Element> elements, bool open)
	{
		this->position = position;
		this->text = text;
		this->open = open;
		this->elements = elements;
		this->setting = setting;
		this->width = width;

		this->onMouseClickEndEvent		= MFUNC (&ComboBox::Event_OnClickEnd, this);
		this->onMouseClickStartEvent	= MFUNC (&ComboBox::Event_OnClickStart, this);
		this->onMouseLeaveEvent			= MFUNC (&ComboBox::Event_OnMouseLeave, this);

		int x = 0, y = 0;
		for (int i = 0; i < elements.size(); i++)
		{
			y++;

			CB_Element* element = &this->elements[i];

			CB_Button<E>* new_button = new CB_Button<E> (

				element->name,
				LOC (10 + x, (y * CB_ELEMENT_HEIGHT) + (10 + (y * 10))),
				LOC (width - 20, CB_ELEMENT_HEIGHT),
				this->setting,
				element,
				open
				);
			AddComponent (new_button);
			if (*setting == element->value)
				this->text = element->name;
		}

		UpdateSize(width, y);
	}

	void UpdateSize(int width, int height)
	{
		if(open)
			this->size = Vector2D (width, ((height+1) * CB_ELEMENT_HEIGHT) + (10 + ((height+1) * CB_ELEMENT_SEPARATOR_WIDTH)));
		else if (!open)
			this->size = Vector2D (width, 30);
	}

	void Draw ()
	{

		if (open)
		{
			Clear (background_color);
			DrawRectangle(LOC(0, 0), LOC(size.x, size.y), Settings::UI::mainColor);
			Panel::Draw();
		}
		else
		{

			DrawRectangle(LOC(0, 0), LOC(size.x, 30), Settings::UI::mainColor);
		}

		DrawFilledRectangle (LOC(0, 0), LOC(size.x, 30), open ? background_color_hovered : isHovered ? background_color_hovered : background_color_closed);

		DrawCenteredString (text, normal_font, text_color, LOC (size.x / 2, 16));

		for (int i = 0; i < elements.size(); i++)
		{
				CB_Element* element = &this->elements[i];
				if (*setting == element->value)
					this->text = element->name;
		}
	}
};
