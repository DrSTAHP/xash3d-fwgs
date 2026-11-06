/*
imgui_hack.cpp - A C++ exit point for Dear ImGui's API providing definitions for embedded hacking/cheating menus
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

#include "imgui_hack.h"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

// C linkage with engine headers
extern "C" {

#include <SDL.h>
#include "sdl2/platform_sdl2.h"
#include "vid_common.h"
#include "client.h"

}

static qboolean gIsInitialized = false;
static bool gIsHackMenuOpen = false;

const char *gszImguiFileExclusionList[IMGUI_MAX_FILE_EXCLUSIONS] = {
	"../imgui.ini"
};

void CL_HackMenuOpen( void )
{
	if( !VID_Imgui_IsInitialized( ) || gIsHackMenuOpen )
		return;

	Key_SetKeyDest( key_menu );
	gIsHackMenuOpen = true;
}

void CL_HackMenuClose( void )
{
	if( !VID_Imgui_IsInitialized( ) || !gIsHackMenuOpen )
		return;

	Key_SetKeyDest( key_game );
	gIsHackMenuOpen = false;
}

qboolean CL_Imgui_IsFileExcluded( const char *pszFilename )
{
	if( !pszFilename )
		return false;
	for( int i = 0; i < ARRAYSIZE( gszImguiFileExclusionList ); i++ )
	{
		if( !Q_strnicmp( pszFilename, gszImguiFileExclusionList[i], Q_strlen( gszImguiFileExclusionList[i] ) ) )
			return true;
	}

	return false;
}

void VID_Imgui_Init_SDL2_GL( void )
{
	if( VID_Imgui_IsInitialized( ) )
		return;

	if( !ImGui::CreateContext( ) )
		return;

	if( !ImGui_ImplOpenGL3_Init( nullptr ) )
		return;

	if( !ImGui_ImplSDL2_InitForOpenGL( reinterpret_cast<SDL_Window *>( host.hWnd ), glw_state.context ) )
		return;

	gIsInitialized = true;
}

void VID_Imgui_DestroyContext( void )
{
	if( !VID_Imgui_IsInitialized( ) )
		return;
	ImGui::DestroyContext( nullptr );
}

void VID_Imgui_Shutdown_SDL2_GL( void )
{
	if( !VID_Imgui_IsInitialized( ) )
		return;

	ImGui_ImplOpenGL3_Shutdown( );
	ImGui_ImplSDL2_Shutdown( );

	VID_Imgui_DestroyContext( );
}

void VID_Imgui_ProcessEvent_SDL2_GL( const SDL_Event *pEvent )
{
	if( !VID_Imgui_IsInitialized( ) || pEvent == nullptr )
		return;

	ImGui_ImplSDL2_ProcessEvent( pEvent );
}

inline qboolean VID_Imgui_IsInitialized( void )
{
	return gIsInitialized;
}

void VID_Imgui_PreRender_SDL2_GL( void )
{
	if( !VID_Imgui_IsInitialized( ) )
		return;

	ImGui_ImplOpenGL3_NewFrame( );
	ImGui_ImplSDL2_NewFrame( );
	ImGui::NewFrame( );
}

void VID_Imgui_Render_SDL2_GL( void )
{
	if( !VID_Imgui_IsInitialized( ) )
		return;

	if( gIsHackMenuOpen )
	{
		bool bIsStillOpen = true;
		ImGui::ShowAboutWindow( &bIsStillOpen );

		if( !bIsStillOpen )
			CL_HackMenuClose( );
	}
}

void VID_Imgui_PostRender_SDL2_GL( void )
{
	if( !VID_Imgui_IsInitialized( ) )
		return;

	ImGui::Render( );
	ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData( ) );
}
