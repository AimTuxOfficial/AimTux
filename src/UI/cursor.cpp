#include "cursor.h"

bool isMouseDown = false;

void Cursor::Draw ()
{
	int x, y;
	input->GetCursorPosition(&x, &y);

	Color color = Color(0, 0, 0, 255);

	DrawLine(Vector2D(x, y), Vector2D(x + 20, y + 10), color);
	DrawLine(Vector2D(x, y), Vector2D(x + 10, y + 20), color);

	DrawLine(Vector2D(x + 10, y + 20), Vector2D(x + 10, y + 10), color);
	DrawLine(Vector2D(x + 10, y + 10), Vector2D(x + 20, y + 10), color);
}