#include "fonts.h"

FONT esp_font = 0;

char* Settings::UI::Fonts::ESP::family = (char *) "Andale Mono";
int Settings::UI::Fonts::ESP::size = 20;
int Settings::UI::Fonts::ESP::flags = FONTFLAG_OUTLINE | FONTFLAG_ANTIALIAS;

void Fonts::SetupFonts()
{
	esp_font = Draw::CreateFont(Settings::UI::Fonts::ESP::family, Settings::UI::Fonts::ESP::size, Settings::UI::Fonts::ESP::flags);
}