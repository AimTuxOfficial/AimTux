#pragma once

#include "component.h"
#include "button.h"
#include "../settings.h"

class ToggleSwitch : public Component
{
protected:
	Color text_color = Color (255, 255, 255, 200);
	Color background_color = Color (45, 45, 55, 25);
	Color background_color_hovered = Color (45, 45, 55, 35);
public:
	bool clickStarted = false;
	bool* setting;
	std::string text = "toggle switch";

	void Event_OnClickStart ()
	{
		clickStarted = true;
	}

	void Event_OnClickEnd ()
	{
		if (clickStarted)
		{
			*setting = !*setting;
		}
	}

	void Event_OnMouseLeave ()
	{
		clickStarted = false;
	}

	ToggleSwitch (std::string text, Vector2D position, Vector2D size, bool* setting)
	{
		this->position = position;
		this->size = size;
		this->text = text;
		this->setting = setting;

		this->onMouseClickEndEvent		= MFUNC (&ToggleSwitch::Event_OnClickEnd, this);
		this->onMouseClickStartEvent	= MFUNC (&ToggleSwitch::Event_OnClickStart, this);
		this->onMouseLeaveEvent			= MFUNC (&ToggleSwitch::Event_OnMouseLeave, this);
	}

	ToggleSwitch (std::string text, Vector2D position, int height, bool* setting)
		: ToggleSwitch (text, position, LOC (height + 25 + Draw::GetTextSize (text.c_str(), normal_font).x, height), setting) { }


	void Draw ()
	{
		Clear (isHovered ? background_color_hovered : background_color);

		int sep = size.y / 4;

		if (!*setting)
		{
			DrawRectangle (LOC(size.x - 25, 5), LOC(size.x - 5, 25), Settings::UI::mainColor);
		}
		else
		{
			DrawRectangle (LOC(size.x - 25, 5), LOC(size.x - 5, 25), Settings::UI::mainColor);
			DrawFilledRectangle (LOC((size.x - 25) + 2, 5 + 2), LOC((size.x - 5) -2, 25 - 2), Settings::UI::mainColor);
		}

		Vector2D textSize = Draw::GetTextSize (text.c_str(), normal_font);

		DrawString (text, normal_font, text_color, LOC ((sep*2) - 10, (size.y/2)-(textSize.y/2)));
	}
};

class ToggleButton : public Button
{
protected:
	Color text_color = Color (255, 255, 255, 255);
	Color hovered_outline_color = Color (200, 200, 200, 20);
	Color background_color = Color (40, 40, 40, 150);
public:
	bool* setting;

	void OnClicked ()
	{
		*setting = !*setting;
	}

	ToggleButton (std::string text, Vector2D position, Vector2D size, bool* setting)
						: Button (text, position, size)
	{
		this->setting = setting;
		this->OnClickedEvent = MFUNC (&ToggleButton::OnClicked, this);
	}

	void Draw ()
	{
		Clear (background_color);

		if (*setting)
		{
			DrawRectangle (LOC (0, 0), size, Settings::UI::mainColor);
		}
		else if (isHovered)
		{
			DrawRectangle (LOC (0, 0), size, hovered_outline_color);
		}

		DrawCenteredString (text, normal_font, text_color, LOC (size.x / 2, size.y / 2));
	}
};

class ToggleSwitchTip : public ToggleSwitch
{
protected:
	Color tt_color = Color(40, 40, 40, 200);
public:
	std::string toolTipText;
	Vector2D toolTipTextSize;
	int x, y;

	ToggleSwitchTip (std::string text, Vector2D position, Vector2D size, bool* setting, std::string toolTipText)
		: ToggleSwitch (text, position, size, setting)
	{
		this->toolTipText = toolTipText;
	}

	void Draw ()
	{
		Clear (isHovered ? background_color_hovered : background_color);

		int sep = size.y / 4;

		if (!*setting)
		{
			DrawRectangle (LOC(size.x - 25, 5), LOC(size.x - 5, 25), Settings::UI::mainColor);
		}
		else
		{
			DrawRectangle (LOC(size.x - 25, 5), LOC(size.x - 5, 25), Settings::UI::mainColor);
			DrawFilledRectangle (LOC((size.x - 25) + 2, 5 + 2), LOC((size.x - 5) -2, 25 - 2), Settings::UI::mainColor);
		}

		if(isHovered){
			input->GetCursorPosition(&x, &y);
			toolTipTextSize = Draw::GetTextSize (toolTipText.c_str(), normal_font);
			Draw::DrawRect (LOC(x + 16, y + 16), LOC(x + (toolTipTextSize.x + 16 + 2), y + 35), tt_color);
			Draw::DrawString(toolTipText, LOC(x + 17, y + 17), text_color, normal_font);
		}

		Vector2D textSize = Draw::GetTextSize (text.c_str(), normal_font);

		DrawString (text, normal_font, text_color, LOC ((sep*2) - 10, (size.y/2)-(textSize.y/2)));

	}
};
