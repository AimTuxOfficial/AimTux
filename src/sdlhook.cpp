#include "sdlhook.h"

#include "interfaces.h"
#include "shortcuts.h"
#include "ATGUI/atgui.h"
#include "Hooks/hooks.h"
#include "Resources/KaiGenGothicCNRegular.h"
#include "ImGUI/examples/imgui_impl_opengles3.h"
#include "ImGUI/examples/libs/gl3w/GL/gl3w.h"
#include "ImGUI/imgui_internal.h" // for 	ImGui::GetCurrentContext()->Font->DisplayOffset
#include <SDL2/SDL.h>
#include <algorithm> //clamp xd

typedef void (*SDL_GL_SwapWindow_t) (SDL_Window*);
typedef int (*SDL_PollEvent_t) (SDL_Event*);

uintptr_t oSwapWindow;
uintptr_t* swapWindowJumpAddress;
SDL_GL_SwapWindow_t  oSDL_GL_SwapWindow;

uintptr_t oPollEvent;
uintptr_t* polleventJumpAddress;
SDL_PollEvent_t oSDL_PollEvent;

typedef int (* eventFilterFn)( void *, SDL_Event * );
eventFilterFn origEventFilter;

static void HandleSDLEvent(SDL_Event * event)
{
    ImGuiIO& io = ImGui::GetIO();
    switch( event->type ){
        case SDL_MOUSEWHEEL:
            if( event->wheel.y > 0 )
                io.MouseWheel = 1;
            if( event->wheel.y < 0 )
                io.MouseWheel = -1;

            return;
        case SDL_MOUSEBUTTONDOWN:
	    if (event->button.button == SDL_BUTTON_LEFT) SDL2::isMouseDown = true;
            if (event->button.button == SDL_BUTTON_RIGHT) io.MouseDown[1] = true;
            if (event->button.button == SDL_BUTTON_MIDDLE) io.MouseDown[2] = true;

            return;
        case SDL_MOUSEBUTTONUP:
	    if (event->button.button == SDL_BUTTON_LEFT) SDL2::isMouseDown = false;
            if (event->button.button == SDL_BUTTON_RIGHT) io.MouseDown[1] = false;
            if (event->button.button == SDL_BUTTON_MIDDLE) io.MouseDown[2] = false;

            return;
        case SDL_TEXTINPUT:
            io.AddInputCharactersUTF8( event->text.text );

            return;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
	    #define key (event->key.keysym.sym & ~SDLK_SCANCODE_MASK)
            io.KeysDown[key] = (event->type == SDL_KEYDOWN);
            io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
            io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
            io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
            io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);

            return;
        case SDL_MOUSEMOTION:
	    SDL2::mouseX = event->motion.x;
	    SDL2::mouseY = event->motion.y;
	  //SDL2::mouseX += event->motion.xrel;
	  //SDL2::mouseY += event->motion.yrel;
	    //cvar->ConsoleDPrintf("x(%d) y(%d) xrel(%d) yrel(%d) -ourx(%d) oury(%d)\n", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel, SDL2::mouseX, SDL2::mouseY);
            return;
    }
}

static void SwapWindow(SDL_Window* window)
{
	static bool bFirst = true;
	if ( bFirst )
	{
	    // This sets the opengl function pointers and stuff
		gl3wInit();
		ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        // Fixup some keycodes for SDL
        io.KeyMap[ImGuiKey_Tab] = SDLK_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
        io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
        io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
        io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
        io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
        io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
        io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
        io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
        io.KeyMap[ImGuiKey_A] = SDLK_a;
        io.KeyMap[ImGuiKey_C] = SDLK_c;
        io.KeyMap[ImGuiKey_V] = SDLK_v;
        io.KeyMap[ImGuiKey_X] = SDLK_x;
        io.KeyMap[ImGuiKey_Y] = SDLK_y;
        io.KeyMap[ImGuiKey_Z] = SDLK_z;

        ImGui_ImplOpenGL3_Init("#version 100");

		bFirst = false;
	}

    ImGuiIO& io = ImGui::GetIO();
    // Setup display size (every frame to accommodate for window resizing)
    int w, h;
    //int display_w, display_h;
    SDL_GetWindowSize(window, &w, &h);
    //SDL_GL_GetDrawableSize(window, &display_w, &display_h);
    Paint::windowWidth = w;
    Paint::windowHeight = h;
    io.DisplaySize = ImVec2((float)w, (float)h);
    //io.DisplayFramebufferScale = ImVec2( 1, 1 );

    ImGui_ImplOpenGL3_NewFrame();

    static double lastTime = 0.0f;
    Uint32 time = SDL_GetTicks();
    double currentTime = time / 1000.0;
    io.DeltaTime = lastTime > 0.0 ? (float)(currentTime - lastTime) : (float)(1.0f / 60.0f);

    io.MouseDrawCursor = UI::isVisible;
    io.WantCaptureMouse = UI::isVisible;
    io.WantCaptureKeyboard = UI::isVisible;
    
    if (UI::isVisible && !SetKeyCodeState::shouldListen)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return;

            HandleSDLEvent(&event);
        }
    }
    
    if( io.WantCaptureMouse ){
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
      
	SDL2::mouseX = std::clamp(SDL2::mouseX, 0, w);
	SDL2::mouseY = std::clamp(SDL2::mouseY, 0, h);
	
        io.MousePos.x = SDL2::mouseX;
        io.MousePos.y = SDL2::mouseY;
	io.MouseDown[0] = SDL2::isMouseDown;
	
        SDL_ShowCursor(io.MouseDrawCursor ? 0: 1);
    }
    

    ImGui::NewFrame();
        ImGui::SetNextWindowPos( ImVec2( 0, 0 ), ImGuiCond_Always );
        ImGui::SetNextWindowSize( ImVec2( w, h ), ImGuiCond_Always );
        ImGui::SetNextWindowBgAlpha( 0.0f );
        ImGui::Begin( "", (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs  );
            UI::SetupColors();
            UI::SetupWindows();
            UI::DrawImWatermark();
            Hooks::PaintImGui(); // Process ImGui Draw Commands
        ImGui::End();
	ImGui::EndFrame();

	ImGui::GetCurrentContext()->Font->DisplayOffset = ImVec2(0.f, 0.f);
	ImGui::GetCurrentContext()->Font->DisplayOffset = ImVec2(0.0f, 0.0f);

	ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    oSDL_GL_SwapWindow(window);
}

void SDL2::HookSwapWindow()
{
    uintptr_t swapwindowFn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, "SDL_GL_SwapWindow")) + 1;
    swapWindowJumpAddress = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(swapwindowFn, 1, 5));
    oSwapWindow = *swapWindowJumpAddress;
    oSDL_GL_SwapWindow = reinterpret_cast<SDL_GL_SwapWindow_t>(oSwapWindow);
    *swapWindowJumpAddress = reinterpret_cast<uintptr_t>(&SwapWindow);
}

void SDL2::UnhookWindow()
{
	*swapWindowJumpAddress = oSwapWindow;
}

static int PollEvent(SDL_Event* event)
{
	Shortcuts::PollEvent(event);

	return oSDL_PollEvent(event);
}

void SDL2::HookPollEvent()
{
    uintptr_t polleventFn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, "SDL_PollEvent")) + 1;
    polleventJumpAddress = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(polleventFn, 1, 5));
    oPollEvent = *polleventJumpAddress;
    oSDL_PollEvent = reinterpret_cast<SDL_PollEvent_t>(oPollEvent);
    *polleventJumpAddress = reinterpret_cast<uintptr_t>(&PollEvent);
}

void SDL2::UnhookPollEvent()
{
	*polleventJumpAddress = oPollEvent;
}
