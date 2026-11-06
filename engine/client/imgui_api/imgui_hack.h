/*
imgui_hack.h - A C entry point for Dear ImGui's C++ API
Copyright (C) 2026 DrSTAHP

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#ifndef IMGUI_HACK_H
#define IMGUI_HACK_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "xash3d_types.h"

#define IMGUI_MAX_FILE_EXCLUSIONS 32
extern const char *gszImguiFileExclusionList[IMGUI_MAX_FILE_EXCLUSIONS];

typedef union SDL_Event SDL_Event;

extern void CL_HackMenuOpen( void );
extern void CL_HackMenuClose( void );

extern qboolean CL_Imgui_IsFileExcluded( const char *pszFilename );

extern void VID_Imgui_Init_SDL2_GL( void );
extern void VID_Imgui_Shutdown_SDL2_GL( void );

extern void VID_Imgui_DestroyContext( void );

extern void VID_Imgui_ProcessEvent_SDL2_GL( const SDL_Event *pEvent );

extern void VID_Imgui_PreRender_SDL2_GL( void );
extern void VID_Imgui_Render_SDL2_GL( void );
extern void VID_Imgui_PostRender_SDL2_GL( void );

extern qboolean VID_Imgui_IsInitialized( void );

#ifdef __cplusplus
}
#endif

#endif 