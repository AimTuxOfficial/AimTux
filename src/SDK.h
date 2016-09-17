#include <cstdint>
#include <dlfcn.h>

/* interface versions */
#define CLIENT_DLL_INTERFACE_VERSION "VClient017"
#define VENGINE_CLIENT_INTERFACE_VERSION "VEngineClient014"
#define VCLIENTENTITYLIST_INTERFACE_VERSION	"VClientEntityList003"

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

/* function prototypes */
typedef void* (*CreateInterfaceFn) (const char*, int*);
typedef void (*FrameStageNotifyFn) (void*, int);

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

enum ItemDefinitionIndex: int {
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516
};

/* helper functions */
template <typename interface> interface* GetInterface(const char* filename, const char* version) {
	void* library = dlopen(filename, RTLD_NOW);

	if (!library)
		return nullptr;

	void* createinterface_sym = dlsym(library, "CreateInterface");

	if (!createinterface_sym)
		return nullptr;

	CreateInterfaceFn factory = reinterpret_cast<CreateInterfaceFn>(createinterface_sym);

	return reinterpret_cast<interface*>(factory(version, nullptr));
}

template <typename Fn> inline Fn GetVirtualFunction(void* baseclass, size_t index) {
	return (Fn)((uintptr_t**)*(uintptr_t***)baseclass)[index];
}

/* generic game classes */
class C_BasePlayer {
	public:
		unsigned char GetLifeState() {
			return *(unsigned char*)((uintptr_t)this + m_lifeState);
		}

		int* GetWeapons() {
			return (int*)((uintptr_t)this + m_hMyWeapons);
		}
};

class C_BaseAttributableItem {
	public:
		int* GetItemDefinitionIndex() {
			return (int*)((uintptr_t)this + m_AttributeManager + m_Item + m_iItemDefinitionIndex);
		}

		int* GetItemIDHigh() {
			return (int*)((uintptr_t)this + m_AttributeManager + m_Item + m_iItemIDHigh);
		}

		int* GetEntityQuality() {
			return (int*)((uintptr_t)this + m_AttributeManager + m_Item + m_iEntityQuality);
		}

		char* GetCustomName() {
			return (char*)((uintptr_t)this + m_AttributeManager + m_Item + m_szCustomName);
		}

		int* GetFallbackPaintKit() {
			return (int*)((uintptr_t)this + m_nFallbackPaintKit);
		}

		int* GetFallbackSeed() {
			return (int*)((uintptr_t)this + m_nFallbackSeed);
		}

		float* GetFallbackWear() {
			return (float*)((uintptr_t)this + m_flFallbackWear);
		}

		int* GetFallbackStatTrak() {
			return (int*)((uintptr_t)this + m_nFallbackStatTrak);
		}
};

/* game interface classes */
class CHLClient {};

class IVEngineClient {
	public:
		int GetLocalPlayer() {
			return GetVirtualFunction<int(*)(void*)>(this, 12)(this);
		}
};

class IClientEntityList {
	public:
		void* GetClientEntity(int index) {
			return GetVirtualFunction<void*(*)(void*, int)>(this, 3)(this, index);
		}
};