#pragma once

#define FCVAR_NONE					0

#define FCVAR_UNREGISTERED			(1<<0)
#define FCVAR_DEVELOPMENTONLY		(1<<1)
#define FCVAR_GAMEDLL				(1<<2)
#define FCVAR_CLIENTDLL				(1<<3)
#define FCVAR_HIDDEN				(1<<4)

#define FCVAR_PROTECTED				(1<<5)
#define FCVAR_SPONLY				(1<<6)
#define FCVAR_ARCHIVE				(1<<7)
#define FCVAR_NOTIFY				(1<<8)
#define FCVAR_USERINFO				(1<<9)
#define FCVAR_CHEAT					(1<<14)

#define FCVAR_PRINTABLEONLY			(1<<10)
#define FCVAR_UNLOGGED				(1<<11)
#define FCVAR_NEVER_AS_STRING		(1<<12)
#define FCVAR_RELEASE				(1<<19)

#define FCVAR_REPLICATED			(1<<13)
#define FCVAR_DEMO					(1<<16)
#define FCVAR_DONTRECORD			(1<<17)

#define FCVAR_NOT_CONNECTED			(1<<22)
#define FCVAR_ARCHIVE_XBOX			(1<<24)
#define FCVAR_SERVER_CAN_EXECUTE	(1<<28)
#define FCVAR_SERVER_CANNOT_QUERY	(1<<29)
#define FCVAR_CLIENTCMD_CAN_EXECUTE	(1<<30)

// Not really ideal but there's already a Color struct used by the GUI.
struct ColorRGBA
{
	ColorRGBA(unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha = 255)
	{
		RGBA[0] = Red;
		RGBA[1] = Green;
		RGBA[2] = Blue;
		RGBA[3] = Alpha;
	}

	unsigned char RGBA[4];
};

class ConVar
{
public:
	float GetFloat()
	{
		typedef float (* oGetFloat)(void*);
		return getvfunc<oGetFloat>(this, 15)(this);
	}

	int GetInt()
	{
		typedef int (* oGetInt)(void*);
		return getvfunc<oGetInt>(this, 16)(this);
	}

	void SetValue(const char* value)
	{
		typedef void (* oSetValue)(void*, const char*);
		return getvfunc<oSetValue>(this, 17)(this, value);
	}

	void SetValue(float value)
	{
		typedef void (* oSetValue)(void*, float);
		return getvfunc<oSetValue>(this, 18)(this, value);
	}

	void SetValue(int value)
	{
		typedef void (* oSetValue)(void*, int);
		return getvfunc<oSetValue>(this, 19)(this, value);
	}

	void SetValue(Color value)
	{
		typedef void (* oSetValue)(void*, Color);
		return getvfunc<oSetValue>(this, 20)(this, value);
	}

	char pad_0x0000[0x4]; //0x0000
	ConVar* pNext; //0x0004
	int32_t bRegistered; //0x0008
	char* pszName; //0x000C
	char* pszHelpString; //0x0010
	int32_t nFlags; //0x0014
	char pad_0x0018[0x4]; //0x0018
	ConVar* pParent; //0x001C
	char* pszDefaultValue; //0x0020
	char* strString; //0x0024
	int32_t StringLength; //0x0028
	float fValue; //0x002C
	int32_t nValue; //0x0030
	int32_t bHasMin; //0x0034
	float fMinVal; //0x0038
	int32_t bHasMax; //0x003C
	float fMaxVal; //0x0040
	void* fnChangeCallback; //0x0044
};

class ICvar : public IAppSystem
{
public:
	ConVar* FindVar(const char *var)
	{
		typedef ConVar* (* oFindVar)(void*, const char*);
		return getvfunc<oFindVar>(this, 15)(this, var);
	}

	template <typename... Values>
	void ConsoleColorPrintf(const ColorRGBA& MsgColor, const char* szMsgFormat, Values... Parameters)
	{
		typedef void (* oConsoleColorPrintf)(void*, const ColorRGBA&, const char*, ...);
		return getvfunc<oConsoleColorPrintf>(this, 25)(this, MsgColor, szMsgFormat, Parameters...);
	}

	template <typename... Values>
	void ConsoleDPrintf(const char* szMsgFormat, Values... Parameters)
	{
		typedef void (* oConsoleDPrintf)(void*, const char*, ...);
		return getvfunc<oConsoleDPrintf>(this, 27)(this, szMsgFormat, Parameters...);
	}
};
