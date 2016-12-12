#pragma once

#define LOC(x,y) Vector2D(x,y)

#include "interfaces.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>
#include "fonts.h"
#include "ImGUI/imgui.h"

namespace Draw
{
	FONT CreateFont(const char* fontName, int size, int flag);
	Vector2D GetTextSize(const wchar_t* input, FONT font);
	Vector2D GetTextSize(std::string text, FONT font);
	void DrawCenteredString(std::string text, Vector2D location, Color color, FONT font);
	void DrawString(std::string text, Vector2D location, Color color, FONT font);
	void DrawRect(Vector2D start, Vector2D end, Color color);
	void DrawBox(Vector2D start, Vector2D end, Color color);
	void DrawLine(Vector2D start, Vector2D end, Color color);
	void DrawOutlinedBox(float x, float y, float w, float h, Color color);
	void DrawCircle(Vector2D position, float points, float radius, Color color);
	void DrawPolygon(int count, Vertex_t* Vertexs, Color color);
	void DrawPolygonOutline(int count, Vertex_t* Vertexs, Color color, Color colorLine);
	void DrawPolyLine(int* x, int* y, int count, Color color);
	void DrawPolyLine(int count, Vertex_t* Vertexs, Color colorLine);

	// ImGui
	void ImStart();
	void ImDrawText(ImVec2 pos, ImColor color, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL);
	void ImDrawCircle(ImVec2 point, ImColor color, float radius, int num_segments = 12, float thickness = 1.0f);
	void ImDrawRect(ImVec2 a, ImVec2 b, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0, float thickness = 1.0f);
	void ImEnd();
}