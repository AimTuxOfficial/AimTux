#include "fonts.h"

FONT title_font = 0;
FONT normal_font = 0;
FONT esp_font = 0;
FONT mono_font = 0;

char* Settings::UI::Fonts::Title::family = (char *) "Arial";
int Settings::UI::Fonts::Title::size = 20;
int Settings::UI::Fonts::Title::flags = FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS;
char* Settings::UI::Fonts::Normal::family = (char *) "Arial";
int Settings::UI::Fonts::Normal::size = 17;
int Settings::UI::Fonts::Normal::flags = FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS;
char* Settings::UI::Fonts::ESP::family = (char *) "Andale Mono";
int Settings::UI::Fonts::ESP::size = 20;
int Settings::UI::Fonts::ESP::flags = FONTFLAG_OUTLINE | FONTFLAG_ANTIALIAS;
char* Settings::UI::Fonts::Mono::family = (char *) "DejaVu Sans Mono";
int Settings::UI::Fonts::Mono::size = 17;
int Settings::UI::Fonts::Mono::flags = FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS;

void Fonts::SetupFonts()
{
	title_font = Draw::CreateFont(Settings::UI::Fonts::Title::family, Settings::UI::Fonts::Title::size, Settings::UI::Fonts::Title::flags);
	normal_font = Draw::CreateFont(Settings::UI::Fonts::Normal::family, Settings::UI::Fonts::Normal::size, Settings::UI::Fonts::Normal::flags);
	esp_font = Draw::CreateFont(Settings::UI::Fonts::ESP::family, Settings::UI::Fonts::ESP::size, Settings::UI::Fonts::ESP::flags);
	mono_font = Draw::CreateFont(Settings::UI::Fonts::Mono::family, Settings::UI::Fonts::Mono::size, Settings::UI::Fonts::Mono::flags);
}