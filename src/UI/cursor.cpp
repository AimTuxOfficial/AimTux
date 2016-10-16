#include "cursor.h"

bool isMouseDown = false;

void Cursor::Draw ()
{
	int x, y;
	input->GetCursorPosition(&x, &y);

	Color white = Color(255, 255, 255, 255);
	Color black = Color(0, 0, 0, 255);

	for (int i = 10; i < 20; i++)
	{
		DrawLine(Vector2D(x, y), Vector2D(x + i, y + 10), white);
		DrawLine(Vector2D(x, y), Vector2D(x + 10, y + i), white);
	}

	DrawLine(Vector2D(x, y), Vector2D(x + 20, y + 10), black);
	DrawLine(Vector2D(x, y), Vector2D(x + 10, y + 20), black);
	DrawLine(Vector2D(x + 10, y + 20), Vector2D(x + 10, y + 10), black);
	DrawLine(Vector2D(x + 10, y + 10), Vector2D(x + 20, y + 10), black);
}