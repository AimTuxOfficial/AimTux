#pragma once

#include "interfaces.h"
#include "Hacks/hacks.h"
#include "shortcuts.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "ImGUI/imgui_internal.h"
#include "ImGUI/fonts/KaiGenGothicCNRegular.h"
#include "ImGUI/fonts/RobotoMonoRegular.h"

typedef void (*SDL_GL_SwapWindow_t) (SDL_Window*);
typedef int (*SDL_PollEvent_t) (SDL_Event*);

namespace SDL2
{
	void SwapWindow(SDL_Window*);
	void UnhookWindow();
	int PollEvent(SDL_Event*);
	void UnhookPollEvent();
}
