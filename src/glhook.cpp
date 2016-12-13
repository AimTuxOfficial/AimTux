#include "glhook.h"

SDL_GLContext aimtux_context = nullptr;

void SDL2::SwapWindow(SDL_Window* window)
{
	static SDL_GL_SwapWindow_t oSDL_GL_SwapWindow = reinterpret_cast<SDL_GL_SwapWindow_t>(original_swap_window);

	static SDL_GLContext original_context = SDL_GL_GetCurrentContext();

	if (!aimtux_context) {
		aimtux_context = SDL_GL_CreateContext(window);
		ImGui_ImplSdl_Init(window);

		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->Clear();
		io.Fonts->AddFontFromMemoryCompressedTTF(RobotoMonoRegular_compressed_data, RobotoMonoRegular_compressed_size, 18.0f);
		io.Fonts->Build();
	}

	SDL_GL_MakeCurrent(window, aimtux_context);

	ImGui_ImplSdl_NewFrame(window);

	Draw::ImStart();
	UI::SwapWindow();
	ESP::SwapWindow();
	Draw::ImEnd();

	UI::SetupColors();
	UI::SetupWindows();

	ImGui::GetIO().MouseDrawCursor = UI::isVisible;
	ImGui::GetIO().WantCaptureMouse = UI::isVisible;
	ImGui::GetCurrentContext()->Font->DisplayOffset = ImVec2(0.f, 0.f);

	ImGui::Render();

	SDL_GL_MakeCurrent(window, original_context);
	oSDL_GL_SwapWindow(window);
}

void SDL2::UnhookWindow()
{
	*swap_window_jump_address = original_swap_window;

	SDL_GL_DeleteContext(aimtux_context);
}

int SDL2::PollEvent(SDL_Event* event)
{
	static SDL_PollEvent_t oSDL_PollEvent = reinterpret_cast<SDL_PollEvent_t>(original_pollevent);

	ImGui_ImplSdl_ProcessEvent(event);

	if (event->key.keysym.sym == SDLK_INSERT && event->type == SDL_KEYDOWN)
		UI::SetVisible(!UI::isVisible);

	return oSDL_PollEvent(event);
}

void SDL2::UnhookPollEvent()
{
	*pollevent_jump_address = original_pollevent;
}
