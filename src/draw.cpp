#include "draw.h"

FONT Draw::CreateFont(const char* fontName, int size, int flag = FONTFLAG_DROPSHADOW)
{
	FONT newFont = surface->CreateFont();

	surface->SetFontGlyphSet(newFont, fontName, size, 0, 0, 0, flag);

	return newFont;
}

Vector2D Draw::GetTextSize(std::string text, FONT font)
{
	int x = 0;
	int y = 0;

	surface->GetTextSize(font, std::wstring (text.begin(), text.end()).c_str(), x, y);

	return LOC(x, y);
}

Vector2D Draw::GetTextSize(const wchar_t* text, FONT font)
{
	int x = 0;
	int y = 0;

	surface->GetTextSize(font, text, x, y);

	return LOC(x, y);
}

void Draw::DrawString(std::string text, Vector2D location, Color color, FONT font)
{
	std::wstring wtext = std::wstring(text.begin(), text.end());

	surface->DrawSetTextColor(color.r, color.g, color.b, color.a);
	surface->DrawSetTextFont(font);
	surface->DrawSetTextPos((int) location.x, (int) location.y);

	surface->DrawPrintText(wtext.c_str(), wcslen(wtext.c_str()));
}

void Draw::DrawCenteredString(std::string text, Vector2D location, Color color, FONT font)
{
	std::wstring wtext = std::wstring(text.begin(), text.end());

	Vector2D textSize = GetTextSize(wtext.c_str(), font);

	location.x -= textSize.x / 2;
	location.y -= textSize.y / 2;

	surface->DrawSetTextColor(color.r, color.g, color.b, color.a);
	surface->DrawSetTextFont(font);
	surface->DrawSetTextPos((int) location.x, (int) location.y);

	surface->DrawPrintText(wtext.c_str(), wcslen(wtext.c_str()));
}

void Draw::DrawCircle(Vector2D position, float points, float radius, Color color)
{
	float step = M_PI * 2.0 / points;

	for (float a = 0; a < ( M_PI * 2.0 ); a += step)
	{
		Vector2D start(radius * cos(a) + position.x, radius * sin(a) + position.y);
		Vector2D end(radius * cos(a + step) + position.x, radius * sin(a + step) + position.y);
		DrawLine(start, end, color);
	}
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

void Draw::DrawOutlinedBox(float x, float y, float w, float h, Color color )
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawOutlinedRect((int) (x - w), (int) y, (int) (x + w), (int) (y + h));

	int div = 3;
	surface->DrawSetColor(color.r / div, color.g / div, color.b / div, 255);
	surface->DrawOutlinedRect((int) (x - w - 1), (int) (y - 1), (int) (x + w + 1), (int) (y + h + 1));
	surface->DrawOutlinedRect((int) (x - w + 1), (int) (y + 1), (int) (x + w - 1), (int) (y + h - 1));
}

void Draw::DrawPolygon(int count, Vertex_t* Vertexs, Color color)
{
	static int Texture = surface->CreateNewTextureID(true);
	unsigned char buffer[4] = { 255, 255, 255, 255 };

	surface->DrawSetTextureRGBA(Texture, buffer, 1, 1);
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawSetTexture(Texture);

	surface->DrawTexturedPolygon(count, Vertexs);
}

void Draw::DrawPolygonOutline(int count, Vertex_t* Vertexs, Color color, Color colorLine)
{
	static int x[128];
	static int y[128];

	Draw::DrawPolygon(count, Vertexs, color);

	for (int i = 0; i < count; i++)
	{
		x[i] = Vertexs[i].m_Position.x;
		y[i] = Vertexs[i].m_Position.y;
	}

	Draw::DrawPolyLine(x, y, count, colorLine);
}

void Draw::DrawPolyLine(int *x, int *y, int count, Color color)
{
	surface->DrawSetColor(color.r, color.g, color.b, color.a);
	surface->DrawPolyLine(x, y, count);
}

void Draw::DrawPolyLine(int count, Vertex_t* Vertexs, Color colorLine)
{
	static int x[128];
	static int y[128];

	for (int i = 0; i < count; i++)
	{
		x[i] = Vertexs[i].m_Position.x;
		y[i] = Vertexs[i].m_Position.y;
	}

	Draw::DrawPolyLine(x, y, count, colorLine);
}

void Draw::ImStart()
{
	int width, height;
	engine->GetScreenSize(width, height);

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiSetCond_Always);
	ImGui::Begin("",
				 (bool*)true,
				 ImVec2(width, height),
				 0.f,
				 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
}

void Draw::ImDrawText(ImVec2 pos, ImColor color, const char* text_begin, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect, ImFontFlags flags)
{
	if (flags & ImFontFlags_Outline)
	{
		ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowFont(), ImGui::GetWindowFontSize(), ImVec2(pos.x - 1, pos.y - 1), ImColor(0, 0, 0, 255), text_begin, text_end, wrap_width, cpu_fine_clip_rect);
		ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowFont(), ImGui::GetWindowFontSize(), ImVec2(pos.x + 2, pos.y), ImColor(0, 0, 0, 255), text_begin, text_end, wrap_width, cpu_fine_clip_rect);
		ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowFont(), ImGui::GetWindowFontSize(), ImVec2(pos.x, pos.y + 2), ImColor(0, 0, 0, 255), text_begin, text_end, wrap_width, cpu_fine_clip_rect);
		ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowFont(), ImGui::GetWindowFontSize(), ImVec2(pos.x - 2, pos.y), ImColor(0, 0, 0, 255), text_begin, text_end, wrap_width, cpu_fine_clip_rect);
	}

	if (flags & ImFontFlags_Shadow)
		ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowFont(), ImGui::GetWindowFontSize(), ImVec2(pos.x + 1, pos.y + 1), ImColor(0, 0, 0, 255), text_begin, text_end, wrap_width, cpu_fine_clip_rect);

	ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowFont(), ImGui::GetWindowFontSize(), pos, color, text_begin, text_end, wrap_width, cpu_fine_clip_rect);
}

void Draw::ImDrawCircle(ImVec2 point, ImColor color, float radius, int num_segments, float thickness)
{
	ImGui::GetWindowDrawList()->AddCircle(point, radius, color, num_segments, thickness);
}

void Draw::ImDrawRect(ImVec2 a, ImVec2 b, ImColor color, float rounding, int rounding_corners_flags, float thickness)
{
	ImGui::GetWindowDrawList()->AddRect(a, b, color, rounding, rounding_corners_flags, thickness);
}

void Draw::ImEnd()
{
	ImGui::End();
}
