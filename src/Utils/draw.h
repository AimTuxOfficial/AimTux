#pragma once

#include "../SDK/vector.h"
#include "../SDK/color.h"
#include "../SDK/definitions.h"
#include "../SDK/ISurface.h"
#include "../settings.h"

enum ImFontFlags
{
	ImFontFlags_None = 1 << 1,
	ImFontFlags_Outline = 1 << 2,
	ImFontFlags_Shadow = 1 << 3
};

namespace Draw {

	extern DrawingBackend currentBackend;

	// Surface
	void Circle( Vector2D position, float points, float radius, Color color );
	void OutlinedCircle( int x0, int y0, int points, int radius, Color col );
	void FilledCircle( Vector2D position, float points, float radius, Color color );
	void Circle3D( const Vector &position, float points, float radius, Color color );
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
	void ImCircle3D( Vector position, float points, float radius, ImColor color );
	void ImCircleFilled( ImVec2 point, ImColor color, float radius, int num_segments = 12 );
	void ImImage( const char* const imagePath, ImVec2 a, ImVec2 b );
	void ImLine( ImVec2 a, ImVec2 b, ImColor color, float thickness = 1.0f );
	void ImRect( ImVec2 a, ImVec2 b, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0, float thickness = 1.0f );
	void ImRect( int x0, int y0, int x1, int y1, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0, float thickness = 1.0f );
	void ImRectFilled( int x0, int y0, int x1, int y1, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0 );
	void ImRectFilled( ImVec2 a, ImVec2 b, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0 );
	void ImText( ImVec2 pos, ImColor color, const char* text_begin, const char* text_end = nullptr, float wrap_width = 0.0f,
				 const ImVec4* cpu_fine_clip_rect = nullptr, ImFontFlags flags = ImFontFlags_None );
	void ImEnd();

	// Hybrid Functions
	bool HyWorldToScreen( const Vector& in, ImVec2 * const out ); // True on Success, false if not on screen
	void HyGetScreenSize( int *width, int *height );
	ImVec2 HyGetTextSize( const char* text, HFont font = 0, const char* text_end = nullptr,
						  bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
	void HyText( int x, int y, ImColor color, const char* text_begin, HFont font = 0, const char* text_end = nullptr,
				 float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = nullptr, ImFontFlags = ImFontFlags_None );
	void HyLine( int x0, int y0, int x1, int y1, ImColor color );
	void HyLine( ImVec2 start, ImVec2 end, ImColor color );
	void HyFilledRectangle( int x0, int y0, int x1, int y1, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0 );
	void HyRectangle( int x0, int y0, int x1, int y1, ImColor color, float rounding = 0.0f, int rounding_corners_flags = ~0 );
	void HyCircle( int x, int y, float radius, ImColor color, int num_segments = 12, float thickness = 1.0f );
	void HyCircleFilled( int x, int y, float radius, ImColor color, int num_segments = 12 );
	void HyCircleFilled( ImVec2 pos, float radius, ImColor color, int num_segments );
	void HyCircle3D( const Vector& position, float points, float radius, ImColor color );
}