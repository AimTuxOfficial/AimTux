#pragma once

#include "../SDK/vector.h"
#include "../SDK/color.h"
#include "../SDK/definitions.h"
#include "../SDK/ISurface.h"
#include "../settings.h"

#include <deque>

enum ImFontFlags
{
	ImFontFlags_None = 1 << 1,
	ImFontFlags_Outline = 1 << 2,
	ImFontFlags_Shadow = 1 << 3
};

enum DrawType
{
	DRAW_LINE,
	DRAW_RECT,
	DRAW_RECT_FILLED,
	DRAW_CIRCLE,
	DRAW_CIRCLE_FILLED,
	DRAW_CIRCLE_3D,
	DRAW_TEXT
};
struct DrawRequest
{
    DrawRequest(){}
	DrawType type;
	int x0, y0, x1, y1;
    int circleSegments;
    float circleRadius;
    float thickness;
	ImColor color;
	ImFontFlags fontflags;
    Vector pos;
    char text[256];
};

namespace Draw {

	extern std::deque<DrawRequest> drawRequests;

	// Surface
	void Circle( Vector2D position, int segments, float radius, Color color );
	void OutlinedCircle( int x0, int y0, int segments, int radius, Color col );
	void FilledCircle( Vector2D position, int segments, float radius, Color color );
	void Circle3D( const Vector &position, int segments, float radius, Color color  );
	void FilledRectangle( int x0, int y0, int x1, int y1, Color col );
	void FilledRectangle( Vector2D start_pos, Vector2D end_pos, Color col );
	void Rectangle( int x0, int y0, int x1, int y1, Color col );
	void Rectangle( Vector2D start_pos, Vector2D end_pos, Color col );
	void Line( int x0, int y0, int x1, int y1, Color col );
	void Line( Vector2D start_pos, Vector2D end_pos, Color col );
	void PolyLine( int* px, int* py, int num_points, Color col );
	void PolyLine( Vertex_t* vertice, int num_points, Color col );
	void TexturedPolygon( int n, Vertex_t* vertice, Color col );
	void TextW( int x, int y, const wchar_t* text, HFont font, Color col );
	void TextW( Vector2D pos, const wchar_t* text, HFont font, Color col );
	void Text( int x, int y, const char* text, HFont font, Color col );
	void Text( Vector2D pos, const char* text, HFont font, Color col );
	void GetTextWSize( const wchar_t* text, HFont font, int& wide, int& tall );
	Vector2D GetTextWSize( const wchar_t* text, HFont font );
	void GetTextSize( const char* text, HFont font, int& wide, int& tall );
	Vector2D GetTextSize( const char* text, HFont font );

	// ImGui
	void ImStart();
	void ImCircle( ImVec2 point, ImColor color, float radius, int num_segments = 12, float thickness = 1.0f );
	void ImCircle3D( Vector position, int segments, float radius, ImColor color );
	void ImCircleFilled( ImVec2 point, ImColor color, float radius, int num_segments = 12 );
	void ImImage( const char* const imagePath, ImVec2 a, ImVec2 b );
	void ImLine( ImVec2 a, ImVec2 b, ImColor color, float thickness = 1.0f );
	void ImRect( ImVec2 a, ImVec2 b, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0, float thickness = 1.0f );
	void ImRect( int x0, int y0, int x1, int y1, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0, float thickness = 1.0f );
	void ImRectFilled( int x0, int y0, int x1, int y1, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0 );
	void ImRectFilled( ImVec2 a, ImVec2 b, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0 );
	void ImText( ImVec2 pos, ImColor color, const char* text_begin, const char* text_end = nullptr, float wrap_width = 0.0f,
				 const ImVec4* cpu_fine_clip_rect = nullptr, ImFontFlags flags = ImFontFlags_Outline );
	void ImEnd();

    // Functions to Add to DrawRequests
    void AddLine( int x0, int y0, int x1, int y1, ImColor color );
	void AddRect( int x0, int y0, int x1, int y1, ImColor color );
	void AddRectFilled( int x0, int y0, int x1, int y1, ImColor color );
	void AddCircle( int x0, int y0, float radius, ImColor color, int segments = 12, float thickness = 1.0f );
	void AddCircleFilled( int x0, int y0, float radius, ImColor color, int segments = 12 );
	void AddCircle3D( const Vector &pos3D, float radius, ImColor color, int segments );
	void AddText( int x0, int y0, const char *text, ImColor color, ImFontFlags flags = ImFontFlags_Outline );
}