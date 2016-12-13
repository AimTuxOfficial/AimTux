#pragma once

#include <list>
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "settings.h"
#include "hacks.h"

namespace UI
{
	extern bool isVisible;

	void SetVisible(bool visible);
	void SwapWindow();
	void SetupColors();
	void SetupWindows();
	bool ColorPicker(float*, bool);
	bool ColorPicker3(float*);
	bool ColorPicker4(float*);
	bool ReverseCheckbox(std::string, bool*, int = 18);
	bool KeyBindButton(ButtonCode_t*);
}
