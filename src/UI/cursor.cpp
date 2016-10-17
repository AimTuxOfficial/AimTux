#include "cursor.h"

bool isMouseDown = false;

void Cursor::Draw ()
{
	int x, y;
	input->GetCursorPosition(&x, &y);

	static Vertex_t MouseVt[3];
	MouseVt[0].Init(Vector2D(x, y));
	MouseVt[1].Init(Vector2D(x + 24, y + 12));
	MouseVt[2].Init(Vector2D(x + 12, y + 24));

	Draw::DrawPolygonOutline(3, MouseVt, Color(255, 255, 255), Color(0, 0, 0));
}