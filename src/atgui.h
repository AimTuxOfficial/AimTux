#pragma once

#include "ImGUI/imgui.h"
#include "settings.h"

namespace UI
{
	extern bool isVisible;

	void setupColors();
	void setupWindows();
	bool ColorPicker(float*, bool);
	bool ColorPicker3(float*);
	bool ColorPicker4(float*);
}
