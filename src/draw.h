#ifndef __DRAW_H_
#define __DRAW_H_

#define LOC(x,y) Vector2D(x,y)

#include "interfaces.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>
#include "fonts.h"

namespace Draw
{
    FONT CreateFont(const char* fontName, int size);
    FONT CreateFont(const char* fontName, int size, int flag);
    Vector2D GetTextSize(const wchar_t* input, FONT font);
    void DrawString(const wchar_t* text, Vector2D location, Color color, FONT font, bool center);
    void DrawRect(Vector2D start, Vector2D end, Color color);
    void DrawBox(Vector2D start, Vector2D end, Color color);
    void DrawLine(Vector2D start, Vector2D end, Color color);
    void DrawOutlinedBox(float x, float y, float w, float h, Color color);
    void DrawCircle(Vector2D position, float radius, float size, Color color);
}

#endif