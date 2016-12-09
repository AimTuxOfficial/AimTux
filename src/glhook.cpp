#include "glhook.h"

SDL_GLContext aimtux_context = nullptr;

void SDL2::SwapWindow(SDL_Window* window)
{
	static SDL_GL_SwapWindow_t oSDL_GL_SwapWindow = reinterpret_cast<SDL_GL_SwapWindow_t>(original_swap_window);
	
	static SDL_GLContext original_context = SDL_GL_GetCurrentContext();
	
	if (!aimtux_context) {
		aimtux_context = SDL_GL_CreateContext(window);
		ImGui_ImplSdl_Init(window);
	}

	SDL_GL_MakeCurrent(window, aimtux_context);

	SDL_Event event;
	while (SDL_PollEvent(&event))
		ImGui_ImplSdl_ProcessEvent(&event);

	ImGui_ImplSdl_NewFrame(window);

	ImGui::GetIO().MouseDrawCursor = true;

	ImGui::Text("Hello, world!");
	
	ImGui::Render();

	SDL_GL_MakeCurrent(window, original_context);

	oSDL_GL_SwapWindow(window);
}

void SDL2::UnhookWindow()
{
	*swap_window_jump_address = original_swap_window;
	
	SDL_GL_DeleteContext(aimtux_context);
}