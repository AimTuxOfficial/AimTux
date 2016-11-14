#include "component.h"

void Component::Clear (Color color)
{
	this->DrawFilledRectangle (Vector2D (0, 0), this->size, color);
}

void Component::DrawString (std::string text, FONT font, Color color, Vector2D position)
{
	Draw::DrawString (text.c_str(), context + position, color, font);
}

void Component::DrawCenteredString (std::string text, FONT font, Color color, Vector2D position)
{
	Draw::DrawCenteredString (text.c_str(), context + position, color, font);
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

void Component::DrawPolygon (Vector2D a, Vector2D b, Vector2D c, Color color)
{
	static Vertex_t vertex[3];

	vertex[0].Init(context + a);
	vertex[1].Init(context + b);
	vertex[2].Init(context + c);

	Draw::DrawPolygon(3, vertex, color);
}
