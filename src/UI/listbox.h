#pragma once

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
	Color background_color = Color (35, 35, 45, 60);
	Color background_color_hovered = Color (35, 35, 45, 100);
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
	Color background_color = Color (25, 25, 35, 250);
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






class LBC_Button : public Button
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color background_color = Color (35, 35, 45, 60);
	Color background_color_hovered = Color (35, 35, 45, 100);
public:
	Config* config;

	void OnClicked ()
	{
		if (current_config != config)
		{
			current_config = config;
			Settings::LoadConfig (*config);
		}
	}

	LBC_Button (std::string text, Vector2D position, Vector2D size, Config* config)
		: Button (text, position, size)
	{
		this->config = config;
		this->OnClickedEvent = MFUNC (&LBC_Button::OnClicked, this);
	}

	void Draw ()
	{
		Clear (isHovered ? background_color_hovered : background_color);

		if (current_config && current_config->name == config->name)
		{
			DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
		}

		DrawCenteredString (text, normal_font, text_color, LOC (size.x / 2, size.y / 2));
	}
};

class ListBox_Config : public Panel
{
protected:
	Color background_color = Color (25, 25, 35, 250);
public:
	std::string text = "listbox";

	ListBox_Config (std::string text, Vector2D position, int width)
	{
		this->position = position;
		this->text = text;
		this->size.x = width;

		Reload ();
	}

	void Reload ()
	{
		childComponents.clear ();

		for (int i = 0; i < configs.size(); i++)
		{
			Config* config = &configs[i];

			LBC_Button* new_button = new LBC_Button (config->name, LOC (10, 10 + (i * LB_ELEMENT_HEIGHT) + (i * LB_ELEMENT_SEPARATOR_WIDTH)), LOC (this->size.x - 20, LB_ELEMENT_HEIGHT), config);
			AddComponent (new_button);
		}

		this->size = Vector2D (this->size.x, (configs.size() * LB_ELEMENT_HEIGHT) + (10 + (configs.size() * LB_ELEMENT_SEPARATOR_WIDTH)));
	}

	void Draw ()
	{
		Clear (background_color);

		DrawRectangle (LOC (0, 0), this->size, Settings::UI::mainColor);

		Panel::Draw ();
	}
};




template<typename E>
class StackedListBox : public Panel
{
protected:
	Color background_color = Color (25, 25, 35, 250);
public:
	std::string text = "listbox";
	std::vector<LB_Element> elements;
	E* setting;

	StackedListBox<E> (std::string text, Vector2D position, int width, int elements_x, E* setting, std::vector<LB_Element> elements)
	{
		this->position = position;
		this->text = text;
		this->elements = elements;
		this->setting = setting;

		int elementWidth = (width / elements_x);

		int x = 0, y = 0;
		for (int i = 0; i < elements.size(); i++)
		{
			if (x == elements_x)
			{
				y++;
				x = 0;
			}

			LB_Element* element = &this->elements[i];

			LB_Button<E>* new_button = new LB_Button<E> (

				element->name,
				LOC (10 + (x * elementWidth), (y * LB_ELEMENT_HEIGHT) + (10 + (y * 10))),
				LOC (elementWidth - 20, LB_ELEMENT_HEIGHT),
				this->setting,
				element

				);
			AddComponent (new_button);

			x++;
		}

		this->size = Vector2D (width, ((y+1) * LB_ELEMENT_HEIGHT) + (10 + ((y+1) * LB_ELEMENT_SEPARATOR_WIDTH)));
	}

	void Draw ()
	{
		Clear (background_color);

		DrawRectangle (LOC (0, 0), this->size, Settings::UI::mainColor);

		Panel::Draw ();
	}
};

//// MULTI SELECT



template<typename T>
class MS_LB_Button : public Button
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color background_color = Color (35, 35, 45, 60);
	Color background_color_hovered = Color (35, 35, 45, 100);
public:
	LB_Element* element;
	std::vector<T>* setting;


	bool IsSelected ()
	{
		return std::find(setting->begin(), setting->end(), element->value) != setting->end();
	}

	void OnClicked ()
	{
		if (!IsSelected())
		{
			setting->push_back (static_cast<Hitbox>(element->value));
		}
		else
		{
			setting->erase (std::remove(setting->begin(), setting->end(), static_cast<Hitbox>(element->value)));
		}
	}

	MS_LB_Button (std::string text, Vector2D position, Vector2D size, std::vector<T>* setting, LB_Element* element)
		: Button (text, position, size)
	{
		this->element = element;
		this->setting = setting;
		this->OnClickedEvent = MFUNC (&MS_LB_Button::OnClicked, this);
	}

	void Draw ()
	{
		Clear (isHovered ? background_color_hovered : background_color);

		if (IsSelected())
		{
			DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
		}

		DrawCenteredString (text, normal_font, text_color, LOC (size.x / 2, size.y / 2));
	}
};

template<typename E>
class MS_ListBox : public Panel
{
protected:
	Color background_color = Color (25, 25, 35, 250);
public:
	std::string text = "multi-select listbox";
	std::vector<LB_Element> elements;
	std::vector<E>* setting;

	MS_ListBox<E> (std::string text, Vector2D position, int width, std::vector<E>* setting, std::vector<LB_Element> elements)
	{
		this->position = position;
		this->text = text;
		this->elements = elements;
		this->setting = setting;

		for (int i = 0; i < elements.size(); i++)
		{
			LB_Element* element = &this->elements[i];

			MS_LB_Button<E>* new_button = new MS_LB_Button<E> (element->name, LOC (10, 10 + (i * LB_ELEMENT_HEIGHT) + (i * LB_ELEMENT_SEPARATOR_WIDTH)), LOC (width - 20, LB_ELEMENT_HEIGHT), this->setting, element);
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
