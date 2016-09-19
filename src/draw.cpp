#include "draw.h"

void CDraw::InitFont(int size, const char* name)
{
    font = surface->CreateFont();
    surface->SetFontGlyphSet(font,name,size,0,0,0,0x80);
}
int CDraw::WidthCalc(const wchar_t* input)
{
	int wide = 0;
    int tall = 0;
	
	surface->GetTextSize( font, input, wide, tall );
	
	return wide;
}
void CDraw::DrawString(bool center, int x, int y, int r,int g, int b, int a, const wchar_t *text, ...)
{
	if ( !text  )
		return;
	
	if ( center )
		x -= WidthCalc( text ) / 2;
		
	surface->DrawSetTextColor ( r, g, b, a );
	surface->DrawSetTextFont ( font );
	surface->DrawSetTextPos ( x, y );
	
	surface->DrawPrintText ( text, 18 );
}
