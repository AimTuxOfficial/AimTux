#include <cstdint>
#include <dlfcn.h>
#include "vector.h"
#include "draw.h"

/* interface versions */
#define CLIENT_DLL_INTERFACE_VERSION "VClient017"
#define VENGINE_CLIENT_INTERFACE_VERSION "VEngineClient014"
#define VCLIENTENTITYLIST_INTERFACE_VERSION	"VClientEntityList003"
#define SURFACE_INTERFACE_VERSION "VGUI_Surface031"
#define PANEL_INTERFACE_VERSION "VGUI_Panel009"


/* network variable offsets */
#define m_lifeState 0x293
#define m_hMyWeapons 0x3528
#define m_AttributeManager 0x34C0
#define m_Item 0x60
#define m_iItemDefinitionIndex 0x268
#define m_iEntityQuality 0x26C
#define m_iItemIDHigh 0x280
#define m_szCustomName 0x340
#define m_nFallbackPaintKit 0x39B0
#define m_nFallbackSeed 0x39B4
#define m_flFallbackWear 0x39B8
#define m_nFallbackStatTrak 0x39BC

/* generic constants */
#define LIFE_ALIVE 0
#define VPANEL unsigned long long

inline void**& getvtable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** getvtable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}
template< typename Fn >
inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}


/* function prototypes */
typedef void* (*CreateInterfaceFn) (const char*, int*);
typedef void  (*FrameStageNotifyFn) (void*, int);
typedef void  (*PaintTraverseFn)    (void*, VPANEL, bool, bool);

/* game enumerated types */
enum ClientFrameStage_t: int {
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

/* helper functions */
template <typename interface> interface* GetInterface(const char* filename, const char* version)
{
	void* library = dlopen(filename, RTLD_NOW);

	if (!library)
		return nullptr;

	void* createinterface_sym = dlsym(library, "CreateInterface");

	if (!createinterface_sym)
		return nullptr;

	CreateInterfaceFn factory = reinterpret_cast<CreateInterfaceFn>(createinterface_sym);

	return reinterpret_cast<interface*>(factory(version, nullptr));
}

template <typename Fn> inline Fn GetVirtualFunction(void* baseclass, size_t index)
{
	return (Fn)((uintptr_t**)*(uintptr_t***)baseclass)[index];
}

/* generic game classes */
class C_BasePlayer {
	public:
	unsigned char GetLifeState()
	{
		return *(unsigned char*)((uintptr_t)this + m_lifeState);
	}

	int* GetWeapons()
	{
		return (int*)((uintptr_t)this + m_hMyWeapons);
	}
};

class C_BaseAttributableItem {
public:
	int* GetItemDefinitionIndex()
	{
		return (int*)((uintptr_t)this + m_AttributeManager + m_Item + m_iItemDefinitionIndex);
	}

	int* GetItemIDHigh()
	{
		return (int*)((uintptr_t)this + m_AttributeManager + m_Item + m_iItemIDHigh);
	}

	int* GetEntityQuality()
	{
		return (int*)((uintptr_t)this + m_AttributeManager + m_Item + m_iEntityQuality);
	}

	char* GetCustomName()
	{
		return (char*)((uintptr_t)this + m_AttributeManager + m_Item + m_szCustomName);
	}

	int* GetFallbackPaintKit()
	{
		return (int*)((uintptr_t)this + m_nFallbackPaintKit);
	}

	int* GetFallbackSeed()
	{
		return (int*)((uintptr_t)this + m_nFallbackSeed);
	}

	float* GetFallbackWear()
	{
		return (float*)((uintptr_t)this + m_flFallbackWear);
	}

	int* GetFallbackStatTrak()
	{
		return (int*)((uintptr_t)this + m_nFallbackStatTrak);
	}
};

class CDebugOverlay
{
public:
	bool ScreenPosition(const Vector& vIn, Vector& vOut)
	{
		typedef bool(* oScreenPosition)(void*, const Vector&, Vector&);
		return getvfunc<oScreenPosition>(this, 11)(this, vIn, vOut);
	}
};

class ISurface
{
public:
	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(* oDrawSetColor)(void*, int, int, int, int);
		getvfunc<oDrawSetColor>(this, 14)(this, r, g, b, a);
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(* oDrawFilledRect)(void*, int, int, int, int);
		getvfunc<oDrawFilledRect>(this, 16)(this, x0, y0, x1, y1);
	}
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(* oDrawLine)(void*, int, int, int, int);
		getvfunc<oDrawLine>(this, 19)(this, x0, y0, x1, y1);
	}
	void DrawSetTextFont(unsigned long long font)
	{
		typedef void(* oDrawSetTextFont)(void*, unsigned long long);
		getvfunc<oDrawSetTextFont>(this, 23)(this, font);
	}
	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(* oDrawSetTextColor)(void*, int, int, int, int);
		getvfunc<oDrawSetTextColor>(this, 24)(this, r, g, b, a);
	}
	void DrawSetTextPos(int x, int y)
	{
		typedef void(* oDrawSetTextPos)(void*, int, int);
		getvfunc<oDrawSetTextPos>(this, 26)(this, x, y);
	}
	void DrawPrintText(const wchar_t *text, int textLen)
	{
		typedef void(* oDrawPrintText)(void*, const wchar_t *, int, int);
		return getvfunc<oDrawPrintText>(this, 28)(this, text, textLen, 0);
	}
	unsigned long long CreateFont()
	{
		typedef unsigned long long(* oCreateFont)(void*);
		return getvfunc<oCreateFont>(this, 71)(this);
	}
	void SetFontGlyphSet(unsigned long long &font, const char *FontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(* oSetFontGlyphSet)(void*, unsigned long long, const char*, int, int, int, int, int, int, int);
		getvfunc<oSetFontGlyphSet>(this, 72)(this, font, FontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	void GetTextSize(unsigned long long font, const wchar_t *text, int &wide, int &tall)
	{
		typedef void(* oGetTextSize)(void*, unsigned long long font, const wchar_t *text, int &wide, int &tall);
		getvfunc<oGetTextSize>(this, 79)(this, font, text, wide, tall);
	}
};

class HLClient
{
public:

};

class IPanel
{
public:
	const char *GetName(VPANEL vguiPanel)
	{
		typedef const char* (* oGetName)(void*, VPANEL);
		return getvfunc<oGetName>(this, 37)(this, vguiPanel);
	}
};

enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,
 
	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
 
	FONT_DRAW_TYPE_COUNT = 2,
};

class CEngineClient
{
public:
	typedef struct player_info_s
	{
		unsigned long long unknown;
		unsigned long long unknown1;
		char			name[128];
		int				userID;
		char			guid[33];
		int32_t			friendsID;
		char			friendsName[128];
		char			_pad[0x28];
	} player_info_t;
	
	bool GetPlayerInfo(int iIndex, player_info_t *pInfo)
	{
		typedef bool(* oGetPlayerInfo)(void*, int, player_info_t*);
		return getvfunc<oGetPlayerInfo>(this, 8)(this, iIndex, pInfo);
	}

	int GetLocalPlayer(void)
	{
		typedef int(* oGetLocalPlayer)(void*);
		return getvfunc< oGetLocalPlayer >(this, 12)(this);
	}
	
	void SendClientCommand (const char* Command)
	{
		typedef void(* oCmd)(void*, const char* cmd);
		return getvfunc<oCmd>(this, 7)(this, Command);
	}
};

class IClientEntityList {
	public:
	void* GetClientEntity(int index)
	{
		return GetVirtualFunction<void*(*)(void*, int)>(this, 3)(this, index);
	}
};