#include "glhook.h"

void SDL2::SwapWindow(SDL_Window* window)
{
	static SDL_GL_SwapWindow_t oSDL_GL_SwapWindow = reinterpret_cast<SDL_GL_SwapWindow_t>(original_swap_window);

	static SDL_GLContext original_context = SDL_GL_GetCurrentContext();
	static SDL_GLContext user_context = NULL;

	if (!user_context) {
		user_context = SDL_GL_CreateContext(window);
		ImGui_ImplSdl_Init(window);
	}

	SDL_GL_MakeCurrent(window, user_context);

	SDL_Event event;
	while (SDL_PollEvent(&event))
		ImGui_ImplSdl_ProcessEvent(&event);

	ImGui_ImplSdl_NewFrame(window);

	ImGui::GetIO().MouseDrawCursor = true;

	ImGui::ShowTestWindow();
	ImGui::Render();

	SDL_GL_MakeCurrent(window, original_context);
	oSDL_GL_SwapWindow(window);
}