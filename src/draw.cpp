#include "draw.h"

FONT Draw::CreateFont (const char* fontName, int size)
{
	FONT newFont = surface->CreateFont ();
	
	surface->SetFontGlyphSet (newFont, fontName, size, 0, 0, 0, 0x80);
	
	return newFont;
}

FONT Draw::CreateFont (const char* fontName, int size, int flag)
{
	FONT newFont = surface->CreateFont ();
	
	surface->SetFontGlyphSet (newFont, fontName, size, 0, 0, 0, flag);
	
	return newFont;
}

int Draw::GetTextWidth (const wchar_t* text, FONT font)
{
	int wide = 0;
	int tall = 0;
	
	surface->GetTextSize(font, text, wide, tall);
	
	return wide;
}

void Draw::DrawString (const wchar_t* text, Vector2D location, Color color, FONT font, bool center)
{
	if (!text)
		return;
	
	if (center)
		location.x -= GetTextWidth(text, font) / 2;
	
	surface->DrawSetTextColor (color.r, color.g, color.b, color.a);
	surface->DrawSetTextFont (font);
	surface->DrawSetTextPos ((int)location.x, (int)location.y);
	
	surface->DrawPrintText (text, wcslen(text));
}

void Draw::DrawRect (Vector2D start, Vector2D end, Color color)
{
	surface->DrawSetColor (color.r, color.g, color.b, color.a);
	surface->DrawFilledRect ((int)start.x, (int)start.y, (int)end.x, (int)end.y);
}

void Draw::DrawBox (Vector2D start, Vector2D end, Color color)
{
	surface->DrawSetColor (color.r, color.g, color.b, color.a);
	surface->DrawOutlinedRect ((int)start.x, (int)start.y, (int)end.x, (int)end.y);
}

void Draw::DrawLine (Vector2D start, Vector2D end, Color color)
{
	surface->DrawSetColor (color.r, color.g, color.b, color.a);
	surface->DrawLine ((int)start.x, (int)start.y, (int)end.x, (int)end.y);
}
