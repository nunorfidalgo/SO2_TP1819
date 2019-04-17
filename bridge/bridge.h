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
	// M�moria partilhada: Jogo
	BRIDGE_API void CriaMemoriaPartilhadaJogo();
	BRIDGE_API void AcedeMemoriaPartilhadaJogo();

	void gotoxy(int x, int y);
}