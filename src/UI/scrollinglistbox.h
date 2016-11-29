#pragma once

#include "panel.h"
#include "button.h"
#include "../settings.h"

#define SLB_ELEMENT_HEIGHT 30
#define SLB_ELEMENT_SEPARATOR_WIDTH 2

struct SLB_Element
{
	std::string name;
	unsigned int value;

	SLB_Element (std::string name, unsigned int value)
	{
		this->name = name;
		this->value = value;
	}
};

template<typename T>
class SLB_Button : public Button
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color background_color = Color (160, 160, 160, 7);
	Color background_color_hovered = Color (160, 160, 160, 12);
public:
	SLB_Element* element;
	T* setting;

	void OnClicked ()
	{
		*static_cast<unsigned int*>((void*)setting) = element->value;
	}

	SLB_Button (std::string text, Vector2D position, Vector2D size, T* setting, SLB_Element* element)
		: Button (text, position, size)
	{
		this->element = element;
		this->setting = setting;
		this->OnClickedEvent = MFUNC (&SLB_Button::OnClicked, this);
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
class ScrollingListBox : public Panel
{
protected:
	Color background_color = Color (160, 160, 160, 4);
public:
	std::string text = "listbox";
	std::vector<SLB_Element> elements;
  Button* upButton;
  Button* downButton;
	E* setting;

  void OnUpClicked()
  {

  }

  void OnDownClicked()
  {
    
  }

	ScrollingListBox<E> (std::string text, Vector2D position, int width, E* setting, std::vector<SLB_Element> elements)
	{
		this->position = position;
		this->text = text;
		this->elements = elements;
		this->setting = setting;

		for (int i = 0; i < elements.size(); i++)
		{
			SLB_Element* element = &this->elements[i];

			SLB_Button<E>* new_button = new SLB_Button<E> (element->name, LOC (5, 5 + (i * SLB_ELEMENT_HEIGHT) + (i * SLB_ELEMENT_SEPARATOR_WIDTH)), LOC (width - 50, SLB_ELEMENT_HEIGHT), this->setting, element);
			AddComponent (new_button);
		}

    upButton = new OutlinedButton("", LOC(width - 40, 5), LOC(35, 30));
    downButton = new OutlinedButton("", LOC(width - 40, (elements.size() * SLB_ELEMENT_HEIGHT) - 7), LOC(35, 30));
    AddComponent(upButton);
    upButton->OnClickedEvent = MFUNC (&ScrollingListBox::OnUpClicked, this);
    AddComponent(downButton);
    upButton->OnClickedEvent = MFUNC (&ScrollingListBox::OnDownClicked, this);
    this->size = Vector2D (width, (elements.size() * SLB_ELEMENT_HEIGHT) + (7 + (elements.size() * SLB_ELEMENT_SEPARATOR_WIDTH)));
	}

	void Draw ()
	{
		Clear (background_color);

		DrawRectangle (LOC (0, 0), this->size, Settings::UI::mainColor);

		Panel::Draw ();
	}
};
