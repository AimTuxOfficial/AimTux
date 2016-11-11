#pragma once

#include "component.h"
#include "../settings.h"
#include "../util.h"
#include <algorithm>

class KeyBind : public Component
{
protected:
    Color text_color			= Color (255, 255, 255, 200);
    Color background_color 		= Color (160, 160, 160, 5);

    int s_caret_stamp;
    Vector2D font_size;

private:
    std::vector<ButtonCode_t> lastPressedKeys;

public:
    ButtonCode_t* key;
    std::string text = "key bind";

    KeyBind (std::string label_text, Vector2D position, Vector2D size, ButtonCode_t* key) : text(label_text)
    {
        this->key = key;
        this->size = size;
        this->position = position;

        // Get the width if the monospaced font
        font_size = Draw::GetTextSize ("j", mono_font);
    }

    void Draw ()
    {
        //Clear (background_color);

        if (isHovered)
        {
            DrawRectangle (LOC (Draw::GetTextSize(text,mono_font).x+15, 0), size, Settings::UI::mainColor);
        }

        DrawFilledRectangle (LOC(Draw::GetTextSize(text,mono_font).x+15, 0), size, background_color);
        DrawString (text, mono_font, text_color, LOC(10, (size.y / 2) - (font_size.y / 2)));
        DrawString (input->ButtonCodeToString(*key), mono_font, text_color, LOC (Draw::GetTextSize(text,mono_font).x+25, (size.y / 2) - (font_size.y / 2)));


    }

    bool GetPressedKeys (std::vector<ButtonCode_t>& pressedKeys)
    {
        bool _isKeyPressed = false;

        for (int i = KEY_0; i <= MOUSE_WHEEL_DOWN; i++)
        {
            ButtonCode_t key = (ButtonCode_t)i;

            if (input->IsButtonDown (key))
            {
                _isKeyPressed = true;
                pressedKeys.push_back (key);
            }
        }

        return _isKeyPressed;
    }

    void Input ()
    {
        if (!isHovered)
        {
            return;
        }

        std::vector<ButtonCode_t> pressedKeys;
        bool isKeyPressed = GetPressedKeys (pressedKeys);

        for (int i = 0; i < pressedKeys.size(); i++)
        {
            *this->key= (ButtonCode_t)pressedKeys[i];

            if (std::find(lastPressedKeys.begin(), lastPressedKeys.end(), *this->key) != lastPressedKeys.end())
            {
                continue;
            }

        }

        lastPressedKeys = pressedKeys;
    }
};
