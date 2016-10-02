#include "component.h"

void Component::Clear (Color color)
{
	this->DrawFilledRectangle (Vector2D (0, 0), this->size, color);
}

void Component::DrawString (std::wstring text, FONT font, Color color, Vector2D position)
{
	Draw::DrawString (text.c_str(), context + position, color, font, false);
}

void Component::DrawCenteredString (std::wstring text, FONT font, Color color, Vector2D position)
{
	Draw::DrawString (text.c_str(), context + position, color, font, true);
}

void Component::DrawRectangle (Vector2D start, Vector2D end, Color color)
{
	Draw::DrawBox (context + start, context + end, color);
}

void Component::DrawFilledRectangle (Vector2D start, Vector2D end, Color color)
{
	Draw::DrawRect (context + start, context + end, color);
}

void Component::DrawLine (Vector2D start, Vector2D end, Color color)
{
	Draw::DrawLine (context + start, context + end, color);
}