#include "draw.h"

void CDraw::InitFont(int size, const char* name)
{
    font = surface->CreateFont();
    surface->SetFontGlyphSet(font,name,size,0,0,0,0x80);
}
int CDraw::WidthCalc(const char* input)
{
	int wide = 0;
    int tall = 0;
	int iBufSize = 255;

	wchar_t* pszUnicode = new wchar_t [ iBufSize ];

	mbstowcs( pszUnicode, input, iBufSize );

	surface->GetTextSize( font, pszUnicode, wide, tall );

	delete [ ] pszUnicode;

	return wide;
}
std::wstring stringToWide(const std::string& text)
{
	std::wstring wide( text.length(), L' ' );
	std::copy( text.begin(), text.end(), wide.begin() );

	return wide;
}
void CDraw::DrawString(bool center,int x, int y, int r,int g, int b, int a,const char *text, ...)
{
	char szBuffer [ 255 ];

	if ( !text  )
		return;
        
	va_list va_args;
    va_start( va_args, text );  
	vsprintf ( szBuffer, text,  va_args);


	if ( center )
		x -= WidthCalc( szBuffer ) / 2;

	surface->DrawSetTextColor ( r, g, b, a );
	surface->DrawSetTextFont ( font );
	surface->DrawSetTextPos ( x, y );

	std::wstring wide = stringToWide( std::string( szBuffer ) );
	surface->DrawPrintText ( wide.c_str(), wide.length() );
}
