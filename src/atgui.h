#pragma once

#include <list>
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_internal.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "settings.h"
#include "Hacks/hacks.h"
#include "Utils/skins.h"
#include "ATGUI/Windows/skinmodelchanger.h"

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
}
