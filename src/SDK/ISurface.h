#pragma once

struct Vertex_t
{
	Vector2D m_Position;
	Vector2D m_TexCoord;

	Vertex_t() {}

	Vertex_t(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}

	void Init(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}
};

typedef Vertex_t FontVertex_t;

class ISurface : public IAppSystem
{
public:
	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void (* oDrawSetColor)(void*, int, int, int, int);
		return getvfunc<oDrawSetColor>(this, 14)(this, r, g, b, a);
	}

	void DrawSetColor(Color color)
	{
		typedef void (* oDrawSetColor)(void*, int, int, int, int);
		return getvfunc<oDrawSetColor>(this, 14)(this, color.r, color.g, color.b, color.a);
	}

	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void (* oDrawFilledRect)(void*, int, int, int, int);
		return getvfunc<oDrawFilledRect>(this, 16)(this, x0, y0, x1, y1);
	}

	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void (* oDrawOutlinedRect)(void*, int, int, int, int);
		return getvfunc<oDrawOutlinedRect>(this, 18)(this, x0, y0, x1, y1);
	}

	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void (* oDrawLine)(void*, int, int, int, int);
		return getvfunc<oDrawLine>(this, 19)(this, x0, y0, x1, y1);
	}

	void DrawPolyLine(int *x, int *y, int count)
	{
		typedef void (* oDrawPolyLine)(void*, int*, int*, int);
		return getvfunc<oDrawPolyLine>(this, 20)(this, x, y, count);
	}

	void DrawSetTextFont(unsigned long long font)
	{
		typedef void (* oDrawSetTextFont)(void*, unsigned long long);
		return getvfunc<oDrawSetTextFont>(this, 23)(this, font);
	}

	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void (* oDrawSetTextColor)(void*, int, int, int, int);
		return getvfunc<oDrawSetTextColor>(this, 24)(this, r, g, b, a);
	}

	void DrawSetTextColor(Color color)
	{
		typedef void (* oDrawSetTextColor)(void*, int, int, int, int);
		return getvfunc<oDrawSetTextColor>(this, 24)(this, color.r, color.g, color.b, color.a);
	}

	void DrawSetTextPos(int x, int y)
	{
		typedef void (* oDrawSetTextPos)(void*, int, int);
		return getvfunc<oDrawSetTextPos>(this, 26)(this, x, y);
	}

	void DrawPrintText(const wchar_t *text, int textLen)
	{
		typedef void (* oDrawPrintText)(void*, const wchar_t *, int, int);
		return getvfunc<oDrawPrintText>(this, 28)(this, text, textLen, 0);
	}

	void DrawSetTextureRGBA(int textureID, unsigned char const* colors, int w, int h)
	{
		typedef void (* oDrawSetTextureRGBA)(void*, int, unsigned char const*, int, int);
		return getvfunc<oDrawSetTextureRGBA>(this, 37)(this, textureID, colors, w, h);
	}

	void DrawSetTexture(int textureID)
	{
		typedef void (* oDrawSetTexture)(void*, int);
		return getvfunc<oDrawSetTexture>(this, 38)(this, textureID);
	}

	int CreateNewTextureID(bool procedural)
	{
		typedef int (* oCreateNewTextureID)(void*, bool);
		return getvfunc<oCreateNewTextureID>(this, 43)(this, procedural);
	}

	HFont CreateFont()
	{
		typedef HFont (* oCreateFont)(void*);
		return getvfunc<oCreateFont>(this, 71)(this);
	}

	void SetFontGlyphSet(unsigned long long &font, const char *FontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void (* oSetFontGlyphSet)(void*, unsigned long long, const char*, int, int, int, int, int, int, int);
		return getvfunc<oSetFontGlyphSet>(this, 72)(this, font, FontName, tall, weight, blur, scanlines, flags, 0, 0);
	}

	void GetTextSize(unsigned long long font, const wchar_t *text, int &wide, int &tall)
	{
		typedef void (* oGetTextSize)(void*, unsigned long long font, const wchar_t *text, int &wide, int &tall);
		return getvfunc<oGetTextSize>(this, 79)(this, font, text, wide, tall);
	}

	void DrawTexturedPolygon(int vtxCount, FontVertex_t *vtx, bool bClipVertices = true)
	{
		typedef void (* oDrawTexturedPolygon)(void*, int, FontVertex_t*, bool);
		return getvfunc<oDrawTexturedPolygon>(this, 106)(this, vtxCount, vtx, bClipVertices);
	}
};
