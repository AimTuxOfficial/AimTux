#ifndef __FONT_H_
#define __FONT_H_

#include <cstdint>
#include <cstddef>
#include <cstring>
#include "settings.h"

extern FONT title_font;
extern FONT normal_font;
extern FONT esp_font;
extern FONT mono_font;

namespace Fonts
{
	void SetupFonts();
}

#endif