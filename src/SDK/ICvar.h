#pragma once

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
	void SetValue(const char* value)
	{
		typedef void (* oSetValue)(void*, const char*);
		getvfunc<oSetValue>(this, 17)(this, value);
	}

	void SetValue(float value)
	{
		typedef void (* oSetValue)(void*, float);
		getvfunc<oSetValue>(this, 18)(this, value);
	}

	void SetValue(int value)
	{
		typedef void (* oSetValue)(void*, int);
		getvfunc<oSetValue>(this, 19)(this, value);
	}

	void SetValue(Color value)
	{
		typedef void (* oSetValue)(void*, Color);
		getvfunc<oSetValue>(this, 20)(this, value);
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

class ICvar
{
public:
	ConVar* FindVar(const char *var)
	{
		typedef void (* oFindVar)(void*, const char*);
		getvfunc<oFindVar>(this, 15)(this, var);
	}

	template <typename... Values>
	void ConsoleColorPrintf(const ColorRGBA& MsgColor, const char* szMsgFormat, Values... Parameters)
	{
		typedef void (* oConsoleColorPrintf)(void*, const ColorRGBA&, const char*, ...);
		getvfunc<oConsoleColorPrintf>(this, 25)(this, MsgColor, szMsgFormat, Parameters...);
	}

	template <typename... Values>
	void ConsoleDPrintf(const char* szMsgFormat, Values... Parameters)
	{
		typedef void (* oConsoleDPrintf)(void*, const char*, ...);
		getvfunc<oConsoleDPrintf>(this, 27)(this, szMsgFormat, Parameters...);
	}
};
