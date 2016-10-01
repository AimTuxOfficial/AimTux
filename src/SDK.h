#ifndef __SDK_H_
#define __SDK_H_

#include <cstdint>
#include <string>
#include "pstring.h"
#include <dlfcn.h>
#include "vector.h"
#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Offsets.h"

/* interface versions */
#define CLIENT_DLL_INTERFACE_VERSION "VClient017"
#define VENGINE_CLIENT_INTERFACE_VERSION "VEngineClient014"
#define VCLIENTENTITYLIST_INTERFACE_VERSION	"VClientEntityList003"
#define SURFACE_INTERFACE_VERSION "VGUI_Surface031"
#define PANEL_INTERFACE_VERSION "VGUI_Panel009"
#define DEBUG_OVERLAY_VERSION "VDebugOverlay004"
#define VMODELINFO_CLIENT_INTERFACE_VERSION "VModelInfoClient004"
#define ENGINETRACE_CLIENT_INTERFACE_VERSION "EngineTraceClient004"
#define INPUTSYSTEM_CLIENT_INTERFACE_VERSION "InputSystemVersion001"

/* generic constants */
#define LIFE_ALIVE 0
#define VPANEL unsigned long long
#define PRINT(c) engine->Print(c)

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


struct CUserCmd;

/* function prototypes */
typedef void* (*CreateInterfaceFn)	(const char*, int*);
typedef void  (*FrameStageNotifyFn) (void*, int);
typedef void  (*PaintTraverseFn)    (void*, VPANEL, bool, bool);
typedef bool  (*CreateMoveFn)		(void*, float, CUserCmd*);

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
	void* library = dlopen(filename, RTLD_NOLOAD | RTLD_NOW);

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


class IHandleEntity
{
public:
	virtual ~IHandleEntity() {};
};
	
class IClientUnknown : public IHandleEntity {};
class IClientRenderable
{
public:
	virtual ~IClientRenderable() {};

	bool SetupBones(matrix3x4_t* pBoneMatrix, int nMaxBones, int nBoneMask, float flCurTime = 0)
	{
		return GetVirtualFunction<bool(*)(void*, matrix3x4_t*, int, int, float)>(this, 13)(this, pBoneMatrix, nMaxBones, nBoneMask, flCurTime);
	}
};
	
class IClientNetworkable
{
public:
	virtual ~IClientNetworkable() {};
};
	
class IClientThinkable
{
public:
	virtual ~IClientThinkable() {};
};
	
class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual ~IClientEntity() {};
};

class C_BaseEntity : public IClientEntity
{
public:
	int* GetModelIndex() {
		return (int*)((uintptr_t)this + offsets.m_nModelIndex);
	}
	
	int GetHealth()
	{
		return *(int*)((uintptr_t)this + offsets.m_iHealth);
	}

	int GetTeam()
	{
		return *(int*)((uintptr_t)this + offsets.m_iTeamNum);
	}

	bool GetDormant()
	{
		return *(bool*)((uintptr_t)this + 0x121);
	}

	unsigned char GetLifeState()
	{
		return *(unsigned char*)((uintptr_t)this + offsets.m_lifeState);
	}

	int* GetWeapons()
	{
		return (int*)((uintptr_t)this + offsets.m_hMyWeapons);
	}
	
	int GetViewModel()
	{
		return *(int*)((uintptr_t)this + offsets.m_hViewModel);
	}
	
	Vector GetVecOrigin()
	{
		return *(Vector*)((uintptr_t)this + offsets.m_vecOrigin);
	}
	
	Vector GetVecViewOffset()
	{
		return *(Vector*)((uintptr_t)this + offsets.m_vecViewOffset);
	}
	
	int GetFlags ()
	{
		return *(int*)((uintptr_t)this + offsets.m_fFlags);
	}
};

/* generic game classes */
class C_BasePlayer : public C_BaseEntity
{
public:
	int* GetWeapons()
	{
		return (int*)((uintptr_t)this + offsets.m_hMyWeapons);
	}
	
	QAngle GetAimPunchAngle ()
	{
		return *(QAngle*)((uintptr_t)this + offsets.m_aimPunchAngle);
	}
	
	int GetActiveWeapon ()
	{
		return *(int*)((uintptr_t)this + offsets.m_hActiveWeapon);
	}
	
	float GetTickBase ()
	{
		return *(float*)((uintptr_t)this + offsets.m_nTickBase);
	}
};


class C_BaseAttributableItem : public C_BaseEntity
{
public:
	int* GetItemDefinitionIndex()
	{
		return (int*)((uintptr_t)this + offsets.m_iItemDefinitionIndex);
	}

	int* GetItemIDHigh()
	{
		return (int*)((uintptr_t)this + offsets.m_iItemIDHigh);
	}

	int* GetEntityQuality()
	{
		return (int*)((uintptr_t)this + offsets.m_iEntityQuality);
	}

	char* GetCustomName()
	{
		return (char*)((uintptr_t)this + offsets.m_szCustomName);
	}

	int* GetFallbackPaintKit()
	{
		return (int*)((uintptr_t)this + offsets.m_nFallbackPaintKit);
	}

	int* GetFallbackSeed()
	{
		return (int*)((uintptr_t)this + offsets.m_nFallbackSeed);
	}

	float* GetFallbackWear()
	{
		return (float*)((uintptr_t)this + offsets.m_flFallbackWear);
	}

	int* GetFallbackStatTrak()
	{
		return (int*)((uintptr_t)this + offsets.m_nFallbackStatTrak);
	}
};

class C_BaseCombatWeapon: public C_BaseAttributableItem
{
public:
	unsigned int GetAmmo ()
	{
		return *(unsigned int*)((uintptr_t)this + offsets.m_iClip1);
	}
	
	bool IsReloading ()
	{
		return *(bool*)((uintptr_t)this + offsets.m_bInReload);
	}
	
	float GetNextPrimaryAttack ()
	{
		return *(float*)((uintptr_t)this + offsets.m_flNextPrimaryAttack);
	}
};

class C_BaseViewModel: public C_BaseEntity {
public:
	int GetWeapon() {
		return *(int*)((uintptr_t)this + offsets.m_hWeapon);
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
	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(* oDrawFilledRect)(void*, int, int, int, int);
		getvfunc<oDrawFilledRect>(this, 18)(this, x0, y0, x1, y1);
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
	struct RecvProp;
	struct RecvTable {
		RecvProp *m_pProps;
		int m_nProps;
		void *m_pDecoder;
		char *m_pNetTableName;
		bool m_bInitialized;
		bool m_bInMainList;
	};

	struct RecvProp {
		char *m_pVarName;
		int m_RecvType;
		int m_Flags;
		int m_StringBufferSize;
		bool m_bInsideArray;
		const void *m_pExtraData;
		RecvProp *m_pArrayProp;
		void* m_ArrayLengthProxy;
		void* m_ProxyFn;
		void* m_DataTableProxyFn;
		RecvTable  *m_pDataTable;
		int m_Offset;
		int m_ElementStride;
		int m_nElements;
		const char *m_pParentArrayPropName;
	};

	struct ClientClass {
		void* m_pCreateFn;
		void* m_pCreateEventFn;
		char *m_pNetworkName;
		RecvTable   *m_pRecvTable;
		ClientClass *m_pNext;
		int m_ClassID;
	};

	ClientClass* GetAllClasses() {
		typedef ClientClass*(* OriginalFn)(void*);
		getvfunc<OriginalFn>(this, 8)(this);
	}
};

class IPanel
{
public:
	const char *GetName(VPANEL vguiPanel)
	{
		typedef const char* (* oGetName)(void*, VPANEL);
		getvfunc<oGetName>(this, 37)(this, vguiPanel);
	}
};

enum class FontFeature: int
{
	FONT_FEATURE_ANTIALIASED_FONTS = 1,
	FONT_FEATURE_DROPSHADOW_FONTS = 2,
	FONT_FEATURE_OUTLINE_FONTS = 6
};

enum FontFlags: int
{
	FONTFLAG_NONE = 0,
	FONTFLAG_ITALIC = 0x1,
	FONTFLAG_UNDERLINE = 0x2,
	FONTFLAG_STRIKEOUT = 0x4,
	FONTFLAG_SYMBOL = 0x8,
	FONTFLAG_ANTIALIAS = 0x10,
	FONTFLAG_GAUSSIANBLUR = 0x20,
	FONTFLAG_ROTARY = 0x40,
	FONTFLAG_DROPSHADOW = 0x80,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
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
	
	void GetScreenSize (int& width, int& height) //5
	{
		typedef void(* oGetScreenSize)(void*, int&, int&);
		return getvfunc<oGetScreenSize>(this, 5)(this, width, height);
	}
	
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
	
	void Print (const char* message)
	{
		char buffer[256];
		sprintf (buffer, "echo %s", message);
		
		typedef void(* oCmd)(void*, const char* cmd);
		return getvfunc<oCmd>(this, 108)(this, buffer);
	}
	
	void GetViewAngles (QAngle& angle) // 18
	{
		typedef void(* oGetViewAngles)(void*, QAngle&);
		return getvfunc<oGetViewAngles>(this, 18)(this, angle);
	}
	
	void SetViewAngles (QAngle& angle) // 19
	{
		typedef void(* oSetViewAngles)(void*, QAngle&);
		return getvfunc<oSetViewAngles>(this, 19)(this, angle);
	}

	void ExecuteClientCmd(const char* pCmd) 
	{
		typedef void(* oCmd)(void*, const char*);
		return getvfunc<oCmd>(this, 108)(this, pCmd);
	}
	
};

class IVModelInfo
{
public:
	int GetModelIndex(const char* Filename) {
		return GetVirtualFunction<int(*)(void*, const char*)>(this, 3)(this, Filename);
	}
};

struct CUserCmd {
	virtual ~CUserCmd() {};
	int command_number;
	int tick_count;
	QAngle viewangles;
	QAngle aimdirection;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	unsigned char impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
	QAngle headangles;
	Vector headoffset;
};

class IClientMode {};

class IClientEntityList {
public:
	C_BaseEntity* GetClientEntity(int index)
	{
		typedef C_BaseEntity* (* oGetClientEntity)(void*, int);
		return getvfunc<oGetClientEntity>(this, 3)(this, index);
	}
};

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

struct cplane_t
{
	Vector normal;
	float dist;
	unsigned char type;
	unsigned char signbits;
	unsigned char pad[2];
};

struct csurface_t
{
	const char* name;
	short surfaceProps;
	unsigned short flags;
};

struct trace_t
{
	Vector startpos;
	Vector endpos;
	cplane_t plane;

	float fraction;

	int contents;
	unsigned int dispFlags;

	bool allsolid;
	bool startsolid;

	float fractionleftsolid;

	csurface_t surface;

	int hitgroup;
	short physicsbone;

	unsigned short worldSurfaceIndex;
	void* m_pEntityHit;
	int hitbox;
};

struct Ray_t
{
	VectorAligned m_Start;
	VectorAligned m_Delta;
	VectorAligned m_StartOffset;
	VectorAligned m_Extents;

	const matrix3x4_t* m_pWorldAxisTransform;

	bool m_IsRay;
	bool m_IsSwept;

	Ray_t() : m_pWorldAxisTransform(NULL) { }

	void Init(Vector& vecStart, Vector& vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;

		m_pWorldAxisTransform = NULL;

		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart;
	}
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(C_BaseEntity *pEntity, int contentsMask) = 0;
	virtual TraceType_t GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(C_BaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};

class IEngineTrace
{
public:
	void TraceRay(const Ray_t &ray, unsigned int fMask, CTraceFilter *pTraceFilter, trace_t *pTrace)
	{
		typedef void (* oTraceRay)(void*, const Ray_t&, unsigned int, CTraceFilter *, trace_t*);
		getvfunc<oTraceRay>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
};

#define MAX_SPLITSCREEN_CLIENT_BITS 2
// this should == MAX_JOYSTICKS in InputEnums.h
#define MAX_SPLITSCREEN_CLIENTS	( 1 << MAX_SPLITSCREEN_CLIENT_BITS ) // 4

#define JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_BUTTON + ((_joystick) * JOYSTICK_MAX_BUTTON_COUNT) + (_button) )
#define JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_POV_BUTTON + ((_joystick) * JOYSTICK_POV_BUTTON_COUNT) + (_button) )
#define JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_AXIS_BUTTON + ((_joystick) * JOYSTICK_AXIS_BUTTON_COUNT) + (_button) )

#define JOYSTICK_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_POV_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_AXIS_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) )

enum
{
	MAX_JOYSTICKS = MAX_SPLITSCREEN_CLIENTS,
	MOUSE_BUTTON_COUNT = 5,
};

enum JoystickAxis_t
{
	JOY_AXIS_X = 0,
	JOY_AXIS_Y,
	JOY_AXIS_Z,
	JOY_AXIS_R,
	JOY_AXIS_U,
	JOY_AXIS_V,
	MAX_JOYSTICK_AXES,
};

enum
{
	JOYSTICK_MAX_BUTTON_COUNT = 32,
	JOYSTICK_POV_BUTTON_COUNT = 4,
	JOYSTICK_AXIS_BUTTON_COUNT = MAX_JOYSTICK_AXES * 2,
};

enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,

	// Joystick
	JOYSTICK_FIRST = MOUSE_LAST + 1,

	JOYSTICK_FIRST_BUTTON = JOYSTICK_FIRST,
	JOYSTICK_LAST_BUTTON = JOYSTICK_BUTTON_INTERNAL( MAX_JOYSTICKS - 1, JOYSTICK_MAX_BUTTON_COUNT - 1 ),
	JOYSTICK_FIRST_POV_BUTTON,
	JOYSTICK_LAST_POV_BUTTON = JOYSTICK_POV_BUTTON_INTERNAL( MAX_JOYSTICKS - 1, JOYSTICK_POV_BUTTON_COUNT - 1 ),
	JOYSTICK_FIRST_AXIS_BUTTON,
	JOYSTICK_LAST_AXIS_BUTTON = JOYSTICK_AXIS_BUTTON_INTERNAL( MAX_JOYSTICKS - 1, JOYSTICK_AXIS_BUTTON_COUNT - 1 ),

	JOYSTICK_LAST = JOYSTICK_LAST_AXIS_BUTTON,

	BUTTON_CODE_LAST,
	BUTTON_CODE_COUNT = BUTTON_CODE_LAST - KEY_FIRST + 1,

	// Helpers for XBox 360
	KEY_XBUTTON_UP = JOYSTICK_FIRST_POV_BUTTON,	// POV buttons
	KEY_XBUTTON_RIGHT,
	KEY_XBUTTON_DOWN,
	KEY_XBUTTON_LEFT,

	KEY_XBUTTON_A = JOYSTICK_FIRST_BUTTON,		// Buttons
	KEY_XBUTTON_B,
	KEY_XBUTTON_X,
	KEY_XBUTTON_Y,
	KEY_XBUTTON_LEFT_SHOULDER,
	KEY_XBUTTON_RIGHT_SHOULDER,
	KEY_XBUTTON_BACK,
	KEY_XBUTTON_START,
	KEY_XBUTTON_STICK1,
	KEY_XBUTTON_STICK2,
	KEY_XBUTTON_INACTIVE_START,

	KEY_XSTICK1_RIGHT = JOYSTICK_FIRST_AXIS_BUTTON,	// XAXIS POSITIVE
	KEY_XSTICK1_LEFT,							// XAXIS NEGATIVE
	KEY_XSTICK1_DOWN,							// YAXIS POSITIVE
	KEY_XSTICK1_UP,								// YAXIS NEGATIVE
	KEY_XBUTTON_LTRIGGER,						// ZAXIS POSITIVE
	KEY_XBUTTON_RTRIGGER,						// ZAXIS NEGATIVE
	KEY_XSTICK2_RIGHT,							// UAXIS POSITIVE
	KEY_XSTICK2_LEFT,							// UAXIS NEGATIVE
	KEY_XSTICK2_DOWN,							// VAXIS POSITIVE
	KEY_XSTICK2_UP,								// VAXIS NEGATIVE
};

class IInputSystem
{
public:
	void EnableInput(bool bEnable)
	{
		typedef void (* oEnableInput)(void*, bool);
		getvfunc<oEnableInput>(this, 11)(this, bEnable);
	}

	void ResetInputState()
	{
		typedef void (* oResetInputState)(void*);
		getvfunc<oResetInputState>(this, 39)(this);
	}

	bool IsButtonDown(ButtonCode_t code)
	{
		typedef void (* oIsButtonDown)(void*, ButtonCode_t);
		getvfunc<oIsButtonDown>(this, 15)(this, code);
	}

	void GetCursorPosition(int* m_pX, int* m_pY)
	{
		typedef void (* oGetCursorPosition)(void*, int*, int*);
		getvfunc<oGetCursorPosition>(this, 56)(this, m_pX, m_pY);
	}

	ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey)
	{
		typedef void (* oVirtualKeyToButtonCode)(void*, int);
		getvfunc<oVirtualKeyToButtonCode>(this, 44)(this, nVirtualKey);
	}

	int ButtonCodeToVirtualKey(ButtonCode_t code)
	{
		typedef void (* oButtonCodeToVirtualKey)(void*, ButtonCode_t);
		getvfunc<oButtonCodeToVirtualKey>(this, 45)(this, code);
	}
};

#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER				(1<<9)	// In water
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   
#define IN_SPEED		(1 << 17)	
#define IN_WALK			(1 << 18)	
#define IN_ZOOM			(1 << 19)	
#define IN_WEAPON1		(1 << 20)	
#define IN_WEAPON2		(1 << 21)	
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	
#define IN_GRENADE2		(1 << 24)	
#define	IN_ATTACK3		(1 << 25)

#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200

// unused
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)
#define CONTENTS_BLOCKLIGHT		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define	MASK_SHOT	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

#endif