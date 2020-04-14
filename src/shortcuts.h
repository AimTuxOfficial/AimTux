#pragma once

#include "SDK/IInputSystem.h"
#include <SDL2/SDL.h>

namespace Shortcuts
{
	void PollEvent(SDL_Event* event);
	void SetKeyCodeState(ButtonCode_t code, bool bPressed);
}
