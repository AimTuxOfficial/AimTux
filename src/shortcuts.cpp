#include "shortcuts.h"
#include "ATGUI/atgui.h"
#include "settings.h"

#include "Hacks/grenadeprediction.h"

void Shortcuts::PollEvent(SDL_Event* event)
{
	if (((event->key.keysym.sym == SDLK_INSERT && event->type == SDL_KEYDOWN))
	|| ((event->key.keysym.mod & KMOD_LALT) && event->key.keysym.sym == SDLK_i && event->type == SDL_KEYDOWN)){
		UI::SetVisible(!UI::isVisible);
    }

	if ( Settings::GrenadePrediction::enabled ){
		if( event->type == SDL_MOUSEWHEEL ){
			if( event->wheel.y > 0 ) { // Scroll up.
				GrenadePrediction::cameraHeight -= 25.0f;
			} else if( event->wheel.y < 0 ) { // Scroll Down.
				GrenadePrediction::cameraHeight += 25.0f;
			}
		}
	}
}

void Shortcuts::SetKeyCodeState(ButtonCode_t code, bool bPressed)
{
#ifdef EXPERIMENTAL_SETTINGS
	if (inputSystem->IsButtonDown(ButtonCode_t::KEY_LALT) && code == ButtonCode_t::KEY_F && bPressed)
		Settings::ThirdPerson::enabled = !Settings::ThirdPerson::enabled;
#endif
}