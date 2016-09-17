#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

class CDraw
{
    public:
    void InitFont(int size, const char* name);
    int WidthCalc(const char* input);
    void DrawString(bool center, int x, int y, int r, int g, int b, int  a, const char* text, ...);
    
    unsigned long long font;
    
};

#endif