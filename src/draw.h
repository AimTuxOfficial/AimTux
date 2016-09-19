#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

class CDraw;

#include "interfaces.h"

#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>

class CDraw
{
public:
    void InitFont(int size, const char* name);
    int WidthCalc(const wchar_t* input);
    void DrawString(bool center, int x, int y, int r, int g, int b, int  a, wchar_t* text);
    
    unsigned long long font;
};

#endif