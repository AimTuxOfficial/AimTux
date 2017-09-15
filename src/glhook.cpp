#include "glhook.h"

SDL_GLContext context = nullptr;

void SDL2::SwapWindow(SDL_Window* window)
{
	static SDL_GL_SwapWindow_t oSDL_GL_SwapWindow = reinterpret_cast<SDL_GL_SwapWindow_t>(oSwapWindow);

	static SDL_GLContext original_context = SDL_GL_GetCurrentContext();

	if (!context)
	{
		context = SDL_GL_CreateContext(window);
		ImGui_ImplSdl_Init(window);

		/*
		ImWchar RobotoMonoRegular_ranges[] = {
				0x0020, 0x007F, // Basic Latin
				0x00A0, 0x00FF, // Latin-1 Supplement
				0x0100, 0x017F, // Latin Extended-A
				0x0180, 0x024F, // Latin Extended-B
				0x0370, 0x03FF, // Greek and Coptic
				0x0400, 0x04FF, // Cyrillic
				0x0500, 0x052F, // Cyrillic Supplementary
				0
		};
		*/

		ImWchar SegoeUI_ranges[] = {
				0x0020, 0x007E, // Basic Latin
				0x00A0, 0x00FF, // Latin-1 Supplement
				0x0100, 0x017F, // Latin Extended-A
				0x0180, 0x024F, // Latin Extended-B
				0x0370, 0x03FF, // Greek and Coptic
				0x0400, 0x04FF, // Cyrillic
				0x0500, 0x052F, // Cyrillic Supplementary
				0
		};


		ImWchar KaiGenGothicCNRegular_ranges[] = {
				0x3000, 0x30FF, // Punctuations, Hiragana, Katakana
				0x31F0, 0x31FF, // Katakana Phonetic Extensions
				0xFF00, 0xFFEF, // Half-width characters
				0x4E00, 0x9FAF, // CJK Ideograms
				0
		};

		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig config;

		// Add SegoeUI as default font
		io.Fonts->AddFontFromMemoryCompressedTTF(SegoeUI_compressed_data, SegoeUI_compressed_size, 18.0f, &config, SegoeUI_ranges);

		// Enable MergeMode and add additional fonts
		config.MergeMode = true;
		io.Fonts->AddFontFromMemoryCompressedBase85TTF(KaiGenGothicCNRegular_compressed_data_base85, 14.0f, &config, KaiGenGothicCNRegular_ranges);
		io.Fonts->Build();
	}

	SDL_GL_MakeCurrent(window, context);

	ImGui_ImplSdl_NewFrame(window);

	ImGui::GetIO().MouseDrawCursor = UI::isVisible;
	ImGui::GetIO().WantCaptureMouse = UI::isVisible;
	ImGui::GetIO().WantCaptureKeyboard = UI::isVisible;

	if (UI::isVisible && !SetKeyCodeState::shouldListen)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return;

			ImGui_ImplSdl_ProcessEvent(&event);
		}
	}

	Draw::ImStart();
	UI::SwapWindow();
	Hooks::PaintImGui(); // Process ImGui Draw Commands
	Draw::ImEnd();

	UI::SetupColors();
	UI::SetupWindows();

	ImGui::GetCurrentContext()->Font->DisplayOffset = ImVec2(0.f, 0.f);

	ImGui::Render();

	SDL_GL_MakeCurrent(window, original_context);
	oSDL_GL_SwapWindow(window);
}

void SDL2::UnhookWindow()
{
	*swapWindowJumpAddress = oSwapWindow;

	SDL_GL_DeleteContext(context);
}

int SDL2::PollEvent(SDL_Event* event)
{
	static SDL_PollEvent_t oSDL_PollEvent = reinterpret_cast<SDL_PollEvent_t>(oPollEvent);

	Shortcuts::PollEvent(event);

	return oSDL_PollEvent(event);
}

void SDL2::UnhookPollEvent()
{
	*polleventJumpAddress = oPollEvent;
}
