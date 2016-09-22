#ifndef SDK_H_INCLUDED
#define SDK_H_INCLUDED

#include <cstdint>
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


/* function prototypes */
typedef void* (*CreateInterfaceFn)	(const char*, int*);
typedef void  (*FrameStageNotifyFn) (void*, int);
typedef void  (*PaintTraverseFn)    (void*, VPANEL, bool, bool);
typedef void  (*CreateMoveFn)		(void*, int sequence_number, float input_sample_frametime, bool active);

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

class IClientEntity {};

class C_BaseEntity: public IClientEntity {
public:
	int* GetModelIndex() {
		return (int*)((uintptr_t)this + offsets.m_nModelIndex);
	}
};

/* generic game classes */
class C_BasePlayer : C_BaseEntity
{
public:
	
	char __buf_0x00[0xCC]; // 0x0
	Vector m_vecAbsVelocity; // 0xCC
	Vector m_vecAbsOrigin; // 0xD8
	Vector m_vecOrigin; // 0xE4
	Vector m_vecAngVelocity; // 0xF0
	QAngle m_angAbsRotation; // 0xFC
	QAngle m_angRotation; // 0x108
	float m_flGravity; // 0x114
	float m_flProxyRandomValue; // 0x118
	int m_iEFlags; // 0x11C
	unsigned char m_nWaterType; // 0x120
	unsigned char m_bDormant; // 0x121
	char __buf_0x122[0x2]; // 0x122
	float m_fEffects; // 0x124
	int m_iTeamNum; // 0x128
	int m_iPendingTeamNum; // 0x12C
	char __buf_0x130[0x4]; // 0x130
	int m_iHealth; // 0x134
	int m_fFlags; // 0x138
	Vector m_vecViewOffset; // 0x13C
	Vector m_vecVelocity; // 0x148
	Vector m_vecBaseVelocity; // 0x154
	QAngle m_angNetworkAngles; // 0x160
	Vector m_vecNetworkOrigin; // 0x16C
	float m_flFriction; // 0x178
	unsigned long long m_hNetworkMoveParent; // 0x17C
	unsigned long long m_hOwnerEntity; // 0x180
	unsigned long long m_hGroundEntity; // 0x184
	char __buf_0x18C[0x100]; // 0x18C
	unsigned char _m_nModelIndex; // 0x28C
	char __buf_0x28D[0x1]; // 0x28D
	unsigned char m_nRenderFX; // 0x28E
	unsigned char m_nRenderMode; // 0x28F
	char m_MoveType; // 0x290
	char m_MoveCollide; // 0x291
	unsigned char m_nWaterLevel; // 0x292
	char __buf_0x293[0x85]; // 0x293
	float m_flUseLookAtAngle; // 0x318
	char __buf_0x31C[0x54]; // 0x31C
	char m_ModelName; // 0x370
	char __buf_0x371[0x7]; // 0x371
	unsigned long long m_Collision; // 0x378
	char __buf_0x380[0x198]; // 0x380
	char m_rgflCoordinateFrame; // 0x518
	char __buf_0x519[0x9AF]; // 0x519
	unsigned char m_bEverHadPredictionErrorsForThisCommand; // 0xEC8
	
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

class C_BaseCombatWeapon: public C_BaseAttributableItem {};

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
	
	void SendClientCommand (const char* Command)
	{
		typedef void(* oCmd)(void*, const char* cmd);
		return getvfunc<oCmd>(this, 108)(this, Command);
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

class CUserCmd
{
public:
	virtual ~CUserCmd(){};
	int command_number;
	int tick_count;
	Vector viewangles;
	float forwardmove;
	float sidemove;	
	float upmove;
	int buttons;
	uint8_t impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
};


class CBaseEntity
{
public:
	char __buf_0x00[0xCC]; // 0x0
	Vector m_vecAbsVelocity; // 0xCC
	Vector m_vecAbsOrigin; // 0xD8
	Vector m_vecOrigin; // 0xE4
	Vector m_vecAngVelocity; // 0xF0
	QAngle m_angAbsRotation; // 0xFC
	QAngle m_angRotation; // 0x108
	float m_flGravity; // 0x114
	float m_flProxyRandomValue; // 0x118
	int m_iEFlags; // 0x11C
	unsigned char m_nWaterType; // 0x120
	unsigned char m_bDormant; // 0x121
	char __buf_0x122[0x2]; // 0x122
	float m_fEffects; // 0x124
	int m_iTeamNum; // 0x128
	int m_iPendingTeamNum; // 0x12C
	char __buf_0x130[0x4]; // 0x130
	int m_iHealth; // 0x134
	int m_fFlags; // 0x138
	Vector m_vecViewOffset; // 0x13C
	Vector m_vecVelocity; // 0x148
	Vector m_vecBaseVelocity; // 0x154
	QAngle m_angNetworkAngles; // 0x160
	Vector m_vecNetworkOrigin; // 0x16C
	float m_flFriction; // 0x178
	unsigned long long m_hNetworkMoveParent; // 0x17C
	unsigned long long m_hOwnerEntity; // 0x180
	unsigned long long m_hGroundEntity; // 0x184
	char __buf_0x18C[0x100]; // 0x18C
	unsigned char _m_nModelIndex; // 0x28C
	char __buf_0x28D[0x1]; // 0x28D
	unsigned char m_nRenderFX; // 0x28E
	unsigned char m_nRenderMode; // 0x28F
	char m_MoveType; // 0x290
	char m_MoveCollide; // 0x291
	unsigned char m_nWaterLevel; // 0x292
	char __buf_0x293[0x85]; // 0x293
	float m_flUseLookAtAngle; // 0x318
	char __buf_0x31C[0x54]; // 0x31C
	char m_ModelName; // 0x370
	char __buf_0x371[0x7]; // 0x371
	unsigned long long m_Collision; // 0x378
	char __buf_0x380[0x198]; // 0x380
	char m_rgflCoordinateFrame; // 0x518
	char __buf_0x519[0x9AF]; // 0x519
	unsigned char m_bEverHadPredictionErrorsForThisCommand; // 0xEC8
};

class IClientEntityList {
	public:
	CBaseEntity* GetClientEntity(int index)
	{
		typedef CBaseEntity* (* oGetClientEntity)(void*, int);
		return getvfunc<oGetClientEntity>(this, 3)(this, index);
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

#endif