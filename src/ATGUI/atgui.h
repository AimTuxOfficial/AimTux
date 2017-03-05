#pragma once

#include "../Hacks/hacks.h"
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_sdl.h"
#include "../ImGUI/imgui_internal.h"
#include "../Utils/skins.h"
#include "../settings.h"
#include "Tabs/aimbottab.h"
#include "Tabs/hvhtab.h"
#include "Tabs/misctab.h"
#include "Tabs/modelstab.h"
#include "Tabs/skinstab.h"
#include "Tabs/triggerbottab.h"
#include "Tabs/visualstab.h"
#include "Windows/colors.h"
#include "Windows/configs.h"
#include "Windows/main.h"
#include "Windows/playerlist.h"
#include "Windows/skinmodelchanger.h"
#include "imgui.h"
#include <list>

namespace UI
{
extern bool isVisible;

void SetVisible(bool visible);
void SwapWindow();
void SetupColors();
void SetupWindows();
bool ColorPicker(float* col, bool alphabar);
bool ColorPicker3(float col[3]);
bool ColorPicker4(float col[4]);
void KeyBindButton(ButtonCode_t* key);
void UpdateWeaponSettings();
void ReloadWeaponSettings();
}

inline void SetTooltip(const char* text)
{
    if (ImGui::IsItemHovered())
	ImGui::SetTooltip("%s", text);
}
