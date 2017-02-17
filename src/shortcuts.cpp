#include "shortcuts.h"

void Shortcuts::PollEvent(SDL_Event* event)
{
	if (((event->key.keysym.sym == SDLK_INSERT && event->type == SDL_KEYDOWN)) || ((event->key.keysym.mod & KMOD_LALT) && event->key.keysym.sym == SDLK_i && event->type == SDL_KEYDOWN))
		UI::SetVisible(!UI::isVisible);
}
