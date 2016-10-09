#ifndef __ICVAR_H
#define __ICVAR_H

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

class ICvar
{
public:
	template <typename... Values> void ConsoleColorPrintf(const ColorRGBA& MsgColor, const char* szMsgFormat, Values... Parameters)
	{
		typedef void (* oConsoleColorPrintf)(void*, const ColorRGBA&, const char*, ...);
		getvfunc<oConsoleColorPrintf>(this, 25)(this, MsgColor, szMsgFormat, Parameters...);
	}

	template <typename... Values> void ConsoleDPrintf(const char* szMsgFormat, Values... Parameters)
	{
		typedef void (* oConsoleDPrintf)(void*, const char*, ...);
		getvfunc<oConsoleDPrintf>(this, 27)(this, szMsgFormat, Parameters...);
	}
};

#endif