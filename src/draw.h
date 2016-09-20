#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#define FONT unsigned long long
#define LOC(x,y) Vector2D (x,y)

#include "interfaces.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>

namespace Draw
{
    FONT    CreateFont      (const char* fontName, int size);
    FONT    CreateFont      (const char* fontName, int size, int flag);
    int     GetTextWidth    (const wchar_t* input, FONT font);
    void    DrawString      (const wchar_t* text, Vector2D location, Color color, FONT font, bool center);
    void    DrawRect        (Vector2D start, Vector2D end, Color color);
}

#endif