#pragma once

#include "imgui_freetype.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>

struct SDL_Window;
typedef union SDL_Event SDL_Event;

IMGUI_API bool ImGui_ImplSdl_Init(SDL_Window* window);
IMGUI_API void ImGui_ImplSdl_Shutdown();
IMGUI_API void ImGui_ImplSdl_NewFrame(SDL_Window* window);
IMGUI_API bool ImGui_ImplSdl_ProcessEvent(SDL_Event* event);

IMGUI_API void ImGui_ImplSdl_InvalidateDeviceObjects();
IMGUI_API bool ImGui_ImplSdl_CreateDeviceObjects();