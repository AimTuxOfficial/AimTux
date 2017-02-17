#pragma once

#include "ATGUI/atgui.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "ImGUI/imgui_internal.h"

namespace Shortcuts
{
	void PollEvent(SDL_Event* event);
}
