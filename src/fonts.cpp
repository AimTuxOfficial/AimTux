#include "fonts.h"

HFont esp_font = 0;

char* Settings::UI::Fonts::ESP::family = (char *) "Andale Mono";
int Settings::UI::Fonts::ESP::size = 12;
int Settings::UI::Fonts::ESP::flags = (int) FontFlags::FONTFLAG_DROPSHADOW;

void Fonts::SetupFonts()
{
	esp_font = Draw::CreateFont(Settings::UI::Fonts::ESP::family, Settings::UI::Fonts::ESP::size, Settings::UI::Fonts::ESP::flags);
}