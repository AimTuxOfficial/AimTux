#include "fonts.h"

FONT title_font = 0;
FONT normal_font = 0;
FONT esp_font = 0;
FONT mono_font = 0;

char* Settings::UI::Fonts::Title::family = (char *) "Arial";
int Settings::UI::Fonts::Title::size = 20;
char* Settings::UI::Fonts::Normal::family = (char *) "Arial";
int Settings::UI::Fonts::Normal::size = 17;
char* Settings::UI::Fonts::ESP::family = (char *) "Andale Mono";
int Settings::UI::Fonts::ESP::size = 20;

void Fonts::SetupFonts()
{
	title_font = Draw::CreateFont(Settings::UI::Fonts::Title::family, Settings::UI::Fonts::Title::size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	normal_font = Draw::CreateFont(Settings::UI::Fonts::Normal::family, Settings::UI::Fonts::Normal::size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	esp_font = Draw::CreateFont(Settings::UI::Fonts::ESP::family, Settings::UI::Fonts::ESP::size, FONTFLAG_OUTLINE | FONTFLAG_ANTIALIAS);
	mono_font = Draw::CreateFont("DejaVu Sans Mono", Settings::UI::Fonts::Normal::size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
}