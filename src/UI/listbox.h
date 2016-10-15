#ifndef __LISTBOX_H_
#define __LISTBOX_H_

#include "panel.h"
#include "button.h"
#include "../settings.h"

#define LB_ELEMENT_HEIGHT 30
#define LB_ELEMENT_SEPARATOR_WIDTH 10

struct LB_Element
{
	std::string name;
	unsigned int value;
	
	LB_Element (std::string name, unsigned int value)
	{
		this->name = name;
		this->value = value;
	}
};

template<typename T>
class LB_Button : public Button
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color background_color = Color (160, 160, 160, 7);
	Color background_color_hovered = Color (160, 160, 160, 12);
public:
	LB_Element* element;
	T* setting;
	
	void OnClicked ()
	{
		*static_cast<unsigned int*>((void*)setting) = element->value;
	}
	
	LB_Button (std::string text, Vector2D position, Vector2D size, T* setting, LB_Element* element)
		: Button (text, position, size)
	{
		this->element = element;
		this->setting = setting;
		this->OnClickedEvent = MFUNC (&LB_Button::OnClicked, this);
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
class ListBox : public Panel
{
protected:
	Color background_color = Color (160, 160, 160, 4);
public:
	std::string text = "listbox";
	std::vector<LB_Element> elements;
	E* setting;
	
	ListBox<E> (std::string text, Vector2D position, int width, E* setting, std::vector<LB_Element> elements)
	{
		this->position = position;
		this->text = text;
		this->elements = elements;
		this->setting = setting;
		
		for (int i = 0; i < elements.size(); i++)
		{
			LB_Element* element = &this->elements[i];
			
			LB_Button<E>* new_button = new LB_Button<E> (element->name, LOC (10, 10 + (i * LB_ELEMENT_HEIGHT) + (i * LB_ELEMENT_SEPARATOR_WIDTH)), LOC (width - 20, LB_ELEMENT_HEIGHT), this->setting, element);
			AddComponent (new_button);
		}
		
		this->size = Vector2D (width, (elements.size() * LB_ELEMENT_HEIGHT) + (10 + (elements.size() * LB_ELEMENT_SEPARATOR_WIDTH)));
	}
	
	void Draw ()
	{
		Clear (background_color);
		
		DrawRectangle (LOC (0, 0), this->size, Settings::UI::mainColor);
		
		Panel::Draw ();
	}
};

#endif