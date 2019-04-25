#pragma once

#include <windows.h>
#include <tchar.h>

#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	// Mémoria partilhada: Jogo
	BRIDGE_API void CriaMemoriaPartilhadaJogo();
	BRIDGE_API int AcedeMemoriaPartilhadaJogo();

	BRIDGE_API void gotoxy(int x, int y);
}