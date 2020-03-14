#include "draw.h"

#include <vector>
#include "../interfaces.h"
#include "../settings.h"
#include "../fonts.h"
#include "../Utils/xorstring.h"
#include <SDL2/SDL.h>
#include "../ImGUI/imgui_internal.h"
#include "../Hacks/esp.h"

std::deque<DrawRequest> Draw::drawRequests = {};

void Draw::Circle( Vector2D position, int segments, float radius, Color color ) {
	float step = ( float ) M_PI * 2.0f / ( float )segments;

	for ( float a = 0; a < ( M_PI * 2.0f ); a += step ) {
		Vector2D start( radius * cosf( a ) + position.x, radius * sinf( a ) + position.y );
		Vector2D end( radius * cosf( a + step ) + position.x, radius * sinf( a + step ) + position.y );
		Line( start, end, color );
	}
}

/* Valve does the heavy lifting on this function */
void Draw::OutlinedCircle( int x0, int y0, int segments, int radius, Color col ) {
	surface->DrawSetColor( col );
	surface->DrawOutlinedCircle( x0, y0, segments, radius );
}

void Draw::FilledCircle( Vector2D position, int segments, float radius, Color color ) {
	std::vector<Vertex_t> vertices;
	float step = ( float ) M_PI * 2.0f / ( float )segments;

	for ( float a = 0; a < ( M_PI * 2.0f ); a += step )
		vertices.push_back( Vertex_t( Vector2D( radius * cosf( a ) + position.x, radius * sinf( a ) + position.y ) ) );

	Draw::TexturedPolygon( ( int ) segments, vertices.data(), color );
}

void Draw::Circle3D( const Vector &position, int segments, float radius, Color color ) {
	float step = ( float ) M_PI * 2.0f / ( float )segments;

	for ( float a = 0; a < ( M_PI * 2.0f ); a += step ) {
		Vector start( radius * cosf( a ) + position.x, radius * sinf( a ) + position.y, position.z );
		Vector end( radius * cosf( a + step ) + position.x, radius * sinf( a + step ) + position.y, position.z );

		Vector start2d, end2d;
		if ( debugOverlay->ScreenPosition( start, start2d ) || debugOverlay->ScreenPosition( end, end2d ) )
			return;

		Draw::Line( Vector2D( start2d.x, start2d.y ), Vector2D( end2d.x, end2d.y ), color );
	}
}

void Draw::FilledRectangle( int x0, int y0, int x1, int y1, Color col ) {
	surface->DrawSetColor( col );
	surface->DrawFilledRect( x0, y0, x1, y1 );
}

void Draw::FilledRectangle( Vector2D start_pos, Vector2D end_pos, Color col ) {
	FilledRectangle( start_pos.x, start_pos.y, end_pos.x, end_pos.y, col );
}

void Draw::Rectangle( int x0, int y0, int x1, int y1, Color col ) {
	surface->DrawSetColor( col );
	surface->DrawOutlinedRect( x0, y0, x1, y1 );
}

void Draw::Rectangle( Vector2D start_pos, Vector2D end_pos, Color col ) {
	Rectangle( start_pos.x, start_pos.y, end_pos.x, end_pos.y, col );
}

void Draw::Line( int x0, int y0, int x1, int y1, Color col ) {
	surface->DrawSetColor( col );
	surface->DrawLine( x0, y0, x1, y1 );
}

void Draw::Line( Vector2D start_pos, Vector2D end_pos, Color col ) {
	Line( start_pos.x, start_pos.y, end_pos.x, end_pos.y, col );
}

void Draw::PolyLine( int* px, int* py, int num_points, Color col ) {
	surface->DrawSetColor( col );
	surface->DrawPolyLine( px, py, num_points );
}

void Draw::PolyLine( Vertex_t* vertice, int num_points, Color col ) {
	static int* points_x = new int[num_points];
	static int* points_y = new int[num_points];
	for ( int i = 0; i < num_points; i++ ) {
		points_x[i] = static_cast<int>(vertice[i].m_Position.x);
		points_y[i] = static_cast<int>(vertice[i].m_Position.y);
	}
	PolyLine( points_x, points_y, num_points, col );
}

void Draw::TexturedPolygon( int n, Vertex_t* vertice, Color col ) {
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	static int texture_id;
	if( !texture_id )
		texture_id = surface->CreateNewTextureID( true );
	surface->DrawSetTextureRGBA( texture_id, buf, 1, 1 );
	surface->DrawSetColor( col );
	surface->DrawSetTexture( texture_id );
	surface->DrawTexturedPolygon( n, vertice );
}

void Draw::TextW( int x, int y, const wchar_t* text, HFont font, Color col ) {
	surface->DrawSetTextPos( x, y );
	surface->DrawSetTextFont( font );
	surface->DrawSetTextColor( col );
	surface->DrawPrintText( text, wcslen( text ) );
}

void Draw::TextW( Vector2D pos, const wchar_t* text, HFont font, Color col ) {
	TextW( pos.x, pos.y, text, font, col );
}

void Draw::Text( int x, int y, const char* text, HFont font, Color col ) {
	std::wstring wc = Util::StringToWstring( text );

	surface->DrawSetTextPos( x, y );
	surface->DrawSetTextFont( font );
	surface->DrawSetTextColor( col );
	surface->DrawPrintText( wc.c_str(), wcslen( wc.c_str() ) );
}

void Draw::Text( Vector2D pos, const char* text, HFont font, Color col ) {
	Text( pos.x, pos.y, text, font, col );
}

void Draw::GetTextWSize( const wchar_t* text, HFont font, int& wide, int& tall ) {
	surface->GetTextSize( font, text, wide, tall );
}

void Draw::GetTextSize( const char* text, HFont font, int& wide, int& tall ) {
	std::wstring wc = Util::StringToWstring( text );

	surface->GetTextSize( font, wc.c_str(), wide, tall );
}

Vector2D Draw::GetTextWSize( const wchar_t* text, HFont font ) {
	int x_res, y_res;
	surface->GetTextSize( font, text, x_res, y_res );
	return Vector2D( x_res, y_res );
}

Vector2D Draw::GetTextSize( const char* text, HFont font ) {
	std::wstring wc = Util::StringToWstring( text );

	int x_res, y_res;
	surface->GetTextSize( font, wc.c_str(), x_res, y_res );
	return Vector2D( x_res, y_res );
}

void Draw::ImStart() {
	int width, height;
	SDL_GetWindowSize( SDL_GL_GetCurrentWindow(), &width, &height );

	ImGui::SetNextWindowPos( ImVec2( 0, 0 ), ImGuiSetCond_Always );
	ImGui::SetNextWindowSize( ImVec2( width, height ), ImGuiSetCond_Always );
	ImGui::Begin( "",
				  ( bool* ) true,
				  ImVec2( width, height ),
				  0.f,
				  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
				  ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs );
}

void Draw::ImText( ImVec2 pos, ImColor color, const char* text_begin, const char* text_end, float wrap_width,
				   const ImVec4* cpu_fine_clip_rect, ImFontFlags flags ) {
    ImColor shading;
    shading.Value.x = 0;
    shading.Value.y = 0;
    shading.Value.z = 0;
    shading.Value.w = color.Value.w / 2;

	if ( flags & ImFontFlags_Outline ) {
		ImGui::GetWindowDrawList()->AddText( ImGui::GetFont(), ImGui::GetFontSize(), ImVec2( pos.x - 1, pos.y - 1 ),
                                             shading, text_begin, text_end, wrap_width,
											 cpu_fine_clip_rect );
		ImGui::GetWindowDrawList()->AddText( ImGui::GetFont(), ImGui::GetFontSize(), ImVec2( pos.x + 2, pos.y ),
                                             shading, text_begin, text_end, wrap_width,
											 cpu_fine_clip_rect );
		ImGui::GetWindowDrawList()->AddText( ImGui::GetFont(), ImGui::GetFontSize(), ImVec2( pos.x, pos.y + 2 ),
                                             shading, text_begin, text_end, wrap_width,
											 cpu_fine_clip_rect );
		ImGui::GetWindowDrawList()->AddText( ImGui::GetFont(), ImGui::GetFontSize(), ImVec2( pos.x - 2, pos.y ),
                                             shading, text_begin, text_end, wrap_width,
											 cpu_fine_clip_rect );
	}

	if ( flags & ImFontFlags_Shadow )
		ImGui::GetWindowDrawList()->AddText( ImGui::GetFont(), ImGui::GetFontSize(), ImVec2( pos.x + 1, pos.y + 1 ),
                                             shading, text_begin, text_end, wrap_width,
											 cpu_fine_clip_rect );

	ImGui::GetWindowDrawList()->AddText( ImGui::GetFont(), ImGui::GetFontSize(), pos, color, text_begin, text_end,
										 wrap_width, cpu_fine_clip_rect );
}

void Draw::ImCircle( ImVec2 point, ImColor color, float radius, int num_segments, float thickness ) {
	ImGui::GetWindowDrawList()->AddCircle( point, radius, color, num_segments, thickness );
}

void Draw::ImCircleFilled( ImVec2 point, ImColor color, float radius, int num_segments ) {
	ImGui::GetWindowDrawList()->AddCircleFilled( point, radius, color, num_segments );
}

void Draw::ImRect( ImVec2 a, ImVec2 b, ImColor color, float rounding, int rounding_corners_flags, float thickness ) {
	ImGui::GetWindowDrawList()->AddRect( a, b, color, rounding, rounding_corners_flags, thickness );
}
void Draw::ImRect( int x0, int y0, int x1, int y1, ImColor color, float rounding, int rounding_corners_flags, float thickness ){
	ImGui::GetWindowDrawList()->AddRect( ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags, thickness );
}
void Draw::ImRectFilled( int x0, int y0, int x1, int y1, ImColor color, float rounding, int rounding_corners_flags ){
	ImGui::GetWindowDrawList()->AddRectFilled( ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags );
}
void Draw::ImRectFilled( ImVec2 a, ImVec2 b, ImColor color, float rounding, int rounding_corners_flags ){
	ImGui::GetWindowDrawList()->AddRectFilled( a, b, color, rounding, rounding_corners_flags );
}
void Draw::ImLine( ImVec2 a, ImVec2 b, ImColor color, float thickness ) {
	ImGui::GetWindowDrawList()->AddLine( a, b, color, thickness );
}

void Draw::ImCircle3D( Vector position, int segments, float radius, ImColor color ) {
	float step = ( float ) M_PI * 2.0f / ( float ) segments;

	for ( float a = 0; a < ( M_PI * 2.0f ); a += step ) {

		Vector start( radius * cosf( a ) + position.x,
					  radius * sinf( a ) + position.y,
					  position.z );
		Vector end( radius * cosf( a + step ) + position.x,
					radius * sinf( a + step ) + position.y,
					position.z );

		ImVec2 start2d, end2d;
		if ( !ESP::WorldToScreen( start, &start2d ) || !ESP::WorldToScreen( end, &end2d ) )
			continue;

		Draw::ImLine( start2d, end2d, color );
	}
}

void Draw::ImEnd() {
	ImGui::End();
}

void Draw::AddLine( int x0, int y0, int x1, int y1, ImColor color ) {
    DrawRequest req = {};
    req.type = DRAW_LINE;
    req.x0 = x0;
    req.y0 = y0;
    req.x1 = x1;
    req.y1 = y1;
    req.color = color;

    drawRequests.push_back( req );
}

void Draw::AddRect( int x0, int y0, int x1, int y1, ImColor color ) {
    DrawRequest req = {};
    req.type = DRAW_RECT;
    req.x0 = x0;
    req.y0 = y0;
    req.x1 = x1;
    req.y1 = y1;
    req.color = color;

    drawRequests.push_back( req );
}

void Draw::AddRectFilled( int x0, int y0, int x1, int y1, ImColor color ) {
    DrawRequest req = {};
    req.type = DRAW_RECT_FILLED;
    req.x0 = x0;
    req.y0 = y0;
    req.x1 = x1;
    req.y1 = y1;
    req.color = color;

    drawRequests.push_back( req );
}

void Draw::AddCircle( int x0, int y0, float radius, ImColor color, int segments, float thickness ) {
    DrawRequest req = {};
    req.type = DRAW_CIRCLE;
    req.x0 = x0;
    req.y0 = y0;
    req.circleRadius = radius;
    req.circleSegments = segments;
    req.thickness = thickness;
    req.color = color;

    drawRequests.push_back( req );
}

void Draw::AddCircleFilled( int x0, int y0, float radius, ImColor color, int segments ) {
    DrawRequest req = {};
    req.type = DRAW_CIRCLE_FILLED;
    req.x0 = x0;
    req.y0 = y0;
    req.circleRadius = radius;
    req.circleSegments = segments;
    req.color = color;

    drawRequests.push_back( req );
}

void Draw::AddCircle3D( const Vector &pos3D, float radius, ImColor color, int segments ) {
    DrawRequest req = {};
    req.type = DRAW_CIRCLE_3D;
    req.pos = pos3D;
    req.circleRadius = radius;
    req.circleSegments = segments;
    req.color = color;

    drawRequests.push_back( req );
}

void Draw::AddText( int x0, int y0, const char *text, ImColor color, ImFontFlags flags ) {
    DrawRequest req = {};
    if( text ){
        strncpy( req.text, text, sizeof( req.text ) );
        req.text[sizeof(req.text) - 1] = '\0';
    }
    req.type = DRAW_TEXT;
    req.x0 = x0;
    req.y0 = y0;
    req.color = color;
    req.fontflags = flags;

    drawRequests.push_back( req );
}