#pragma once

#include <windows.h>
#include <locale.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "com.h"
#include "jogo.h"

#define SERVIDOR TEXT("Servidor:")
#define CLIENTE TEXT("Cliente:")

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	BRIDGE_API void gotoxy(int x, int y);
	
}