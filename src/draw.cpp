#include "draw.h"

FONT Draw::CreateFont(const char* fontName, int size)
{
	FONT newFont = surface->CreateFont();
	
	surface->SetFontGlyphSet(newFont, fontName, size, 0, 0, 0, 0x80);
	
	return newFont;
}

FONT Draw::CreateFont(const char* fontName, int size, int flag)
{
	FONT newFont = surface->CreateFont();
	
	surface->SetFontGlyphSet(newFont, fontName, size, 0, 0, 0, flag);
	
	return newFont;
}

Vector2D Draw::GetTextSize(const wchar_t* text, FONT font)
{
	int wide = 0;
	int tall = 0;
	
	surface->GetTextSize(font, text, wide, tall);
	
	return LOC(wide, tall);
}

void Draw::DrawString(const wchar_t* text, Vector2D location, Color color, FONT font, bool center)
{
	if (!text)
		return;
	
	if (center)
	{
		Vector2D textSize = GetTextSize(text, font);
		
		location.x -= textSize.x / 2;
		location.y -= textSize.y / 2;
	}
	
	surface->DrawSetTextColor(color.r, color.g, color.b, color.a);
	surface->DrawSetTextFont(font);
	surface->DrawSetTextPos((int) location.x, (int) location.y);
	
	surface->DrawPrintText(text, wcslen(text));
}

void Draw::DrawRect(Vector2D start, Vector2D end, Color color)
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawFilledRect((int) start.x, (int) start.y, (int) end.x, (int) end.y);
}

void Draw::DrawBox(Vector2D start, Vector2D end, Color color)
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawOutlinedRect((int) start.x, (int) start.y, (int) end.x, (int) end.y);
}

void Draw::DrawLine(Vector2D start, Vector2D end, Color color)
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawLine((int) start.x, (int) start.y, (int) end.x, (int) end.y);
}

void Draw::DrawOutlinedBox (float x, float y, float w, float h, Color color )
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawOutlinedRect(x - w, y, x + w, y + h );
	
	int div = 3;
	surface->DrawSetColor(color.r/div, color.g/div, color.b/div, 255);
	surface->DrawOutlinedRect(x - w - 1, y - 1, x + w + 1, y + h + 1);
	surface->DrawOutlinedRect(x - w + 1, y + 1, x + w - 1, y + h - 1);
}
