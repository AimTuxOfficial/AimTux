#include "draw.h"

void ::Draw::Circle(Vector2D position, float points, float radius, Color color)
{
	float step = M_PI * 2.0 / points;

	for (float a = 0; a < ( M_PI * 2.0 ); a += step)
	{
		Vector2D start(radius * cos(a) + position.x, radius * sin(a) + position.y);
		Vector2D end(radius * cos(a + step) + position.x, radius * sin(a + step) + position.y);
		Line(start, end, color);
	}
}

void Draw::FilledRectangle(int x0, int y0, int x1, int y1, Color col)
{
	surface->DrawSetColor(col);
	surface->DrawFilledRect(x0, y0, x1, y1);
}

void Draw::FilledRectangle(Vector2D start_pos, Vector2D end_pos, Color col)
{
	FilledRectangle(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
}

void Draw::Rectangle(int x0, int y0, int x1, int y1, Color col)
{
	surface->DrawSetColor(col);
	surface->DrawOutlinedRect(x0, y0, x0 + x1, y0 + y1);
}

void Draw::Rectangle(Vector2D start_pos, Vector2D end_pos, Color col)
{
	Rectangle(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
}

void Draw::Line(int x0, int y0, int x1, int y1, Color col)
{
	surface->DrawSetColor(col);
	surface->DrawLine(x0, y0, x1, y1);
}
void Draw::Line(Vector2D start_pos, Vector2D end_pos, Color col)
{
	Line(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
}

void Draw::PolyLine(int* px, int* py, int num_points, Color col)
{
	surface->DrawSetColor(col);
	surface->DrawPolyLine(px, py, num_points);
}

void Draw::PolyLine(Vertex_t* vertice, int num_points, Color col)
{
	static int* points_x = new int[num_points];
	static int* points_y = new int[num_points];
	for (int i = 0; i < num_points; i++)
	{
		points_x[i] = static_cast<int>(vertice[i].m_Position.x);
		points_y[i] = static_cast<int>(vertice[i].m_Position.y);
	}
	PolyLine(points_x, points_y, num_points, col);
}

void Draw::TexturedPolygon(int n, Vertex_t* vertice, Color col)
{
	static int texture_id = surface->CreateNewTextureID(true);
	static unsigned char buf[4] = {255, 255, 255, 255};
	surface->DrawSetTextureRGBA(texture_id, buf, 1, 1);
	surface->DrawSetColor(col);
	surface->DrawSetTexture(texture_id);
	surface->DrawTexturedPolygon(n, vertice);
}

void Draw::TextW(int x, int y, const wchar_t* text, FONT font, Color col)
{
	surface->DrawSetTextPos(x, y);
	surface->DrawSetTextFont(font);
	surface->DrawSetTextColor(col);
	surface->DrawPrintText(text, wcslen(text));
}

void Draw::TextW(Vector2D pos, const wchar_t* text, FONT font, Color col)
{
	TextW(pos.x, pos.y, text, font, col);
}

void Draw::Text(int x, int y, const char* text, FONT font, Color col)
{
	std::wstring wc(strlen(text) + 1, L'#');
	mbstowcs(&wc[0], text, strlen(text) + 1);

	surface->DrawSetTextPos(x, y);
	surface->DrawSetTextFont(font);
	surface->DrawSetTextColor(col);
	surface->DrawPrintText(wc.c_str(), wcslen(wc.c_str()));
}

void Draw::Text(Vector2D pos, const char* text, FONT font, Color col)
{
	Text(pos.x, pos.y, text, font, col);
}

void Draw::GetTextWSize(const wchar_t* text, FONT font, int& wide, int& tall)
{
	surface->GetTextSize(font, text, wide, tall);
}

void Draw::GetTextSize(const char* text, FONT font, int& wide, int& tall)
{
	std::string stext = std::string(text);
	std::wstring wtext = std::wstring(stext.begin(), stext.end());
	surface->GetTextSize(font, wtext.c_str(), wide, tall);
}

Vector2D Draw::GetTextWSize(const wchar_t* text, FONT font)
{
	int x_res, y_res;
	surface->GetTextSize(font, text, x_res,y_res);
	return Vector2D(x_res, y_res);
}

Vector2D Draw::GetTextSize(const char* text, FONT font)
{
	std::string stext = std::string(text);
	std::wstring wtext = std::wstring(stext.begin(), stext.end());

	int x_res, y_res;
	surface->GetTextSize(font, wtext.c_str(), x_res, y_res);
	return Vector2D(x_res, y_res);
}

FONT Draw::CreateFont(const char* fontName, int size, int flag)
{
	FONT newFont = surface->CreateFont();
	surface->SetFontGlyphSet(newFont, fontName, size, 0, 0, 0, flag);
	return newFont;
}

void Draw::ImStart()
{
	int width, height;
	SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &width, &height);

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