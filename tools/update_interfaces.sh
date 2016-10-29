#!/bin/bash

function findInterface {
    interface=$(strings ./csgo/bin/linux64/client_client.so | grep -P "$2")
    echo "#define $1 \"$interface\""
}

findInterface "CLIENT_DLL_INTERFACE_VERSION" "VClient(\d+)$"
findInterface "VENGINE_CLIENT_INTERFACE_VERSION" "VEngineClient(\d+)$"
findInterface "VCLIENTENTITYLIST_INTERFACE_VERSION" "VClientEntityList(\d+)$"
findInterface "SURFACE_INTERFACE_VERSION" "VGUI_Surface(\d+)$"
findInterface "PANEL_INTERFACE_VERSION" "VGUI_Panel(\d+)$"
findInterface "DEBUG_OVERLAY_VERSION" "VDebugOverlay(\d+)$"
findInterface "VMODELINFO_CLIENT_INTERFACE_VERSION" "VModelInfoClient(\d+)$"
findInterface "VMODELRENDER_CLIENT_INTERFACE_VERSION" "VEngineModel(\d+)$"
findInterface "ENGINETRACE_CLIENT_INTERFACE_VERSION" "EngineTraceClient(\d+)$"
findInterface "INPUTSYSTEM_CLIENT_INTERFACE_VERSION" "InputSystemVersion(\d+)$"
findInterface "MATERIALSYSTEM_CLIENT_INTERFACE_VERSION" "VMaterialSystem(\d+)$"
findInterface "ENGINECVAR_INTERFACE_VERSION" "VEngineCvar(\d+)$"
findInterface "ENGINEEFFECTS_INTERFACE_VERSION" "VEngineEffects(\d+)$"
findInterface "GAMEEVENTSMANAGER2_INTERFACE_VERSION" "GAMEEVENTSMANAGER(\d+)$"
findInterface "PHYSICS_CLIENT_INTERFACE_VERSION" "VPhysicsSurfaceProps(\d+)$"
