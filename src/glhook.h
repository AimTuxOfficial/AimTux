#pragma once

#include "interfaces.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"

typedef void (*SDL_GL_SwapWindow_t) (SDL_Window*);

namespace SDL2
{
	void SwapWindow(SDL_Window*);
}