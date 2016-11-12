#include "fonts.h"

FONT title_font = 0;
FONT normal_font = 0;
FONT esp_font = 0;
FONT mono_font = 0;

void Fonts::SetupFonts()
{
	title_font = Draw::CreateFont(cSettings.UI.Fonts.Title.family, cSettings.UI.Fonts.Title.size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	normal_font = Draw::CreateFont(cSettings.UI.Fonts.Normal.family, cSettings.UI.Fonts.Normal.size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
	esp_font = Draw::CreateFont(cSettings.UI.Fonts.ESP.family, cSettings.UI.Fonts.ESP.size, FONTFLAG_OUTLINE | FONTFLAG_ANTIALIAS);
	mono_font = Draw::CreateFont(cSettings.UI.Fonts.Mono.family, cSettings.UI.Fonts.Mono.size, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS);
}