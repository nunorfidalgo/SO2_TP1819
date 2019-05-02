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

#define MUTEX_MENSAGEM TEXT("MutexMensagem")
#define EVENTO_MENSAGEM TEXT("EventoMensagem")
#define SHM_MENSAGEM TEXT("MemPartMensagem")

#define MUTEX_JOGO TEXT("MutexJogo")
#define EVENTO_JOGO TEXT("EventoJogo")
#define SHM_JOGO TEXT("MemPartJogo")

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	// Mémoria partilhada: Jogo
	/*BRIDGE_API void CriaMemoriaPartilhadaJogo();
	BRIDGE_API int AcedeMemoriaPartilhadaJogo();*/
	/*BRIDGE_API Pacote *CriaMemPartCom(HANDLE &hMapMem);
	BRIDGE_API Pacote *AcedeMemPartCom(HANDLE &hMapMem);*/

	// utils.cpp
	BRIDGE_API void gotoxy(int x, int y);
}