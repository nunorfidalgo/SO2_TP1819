#pragma once

#include <windows.h>
#include <locale.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "mensagem.h"
#include "jogo.h"
#include "sinc.h"

#define SERVIDOR TEXT("Servidor")
#define CLIENTE TEXT("Cliente")

// tamanho padrão da linha de comandos do windows
#define COLUNAS 41 // x
#define LINHAS 26 // y

#define VEL_JOGO 500

#define MUTEX_MENSAGEM TEXT("MutexMensagem")
#define EVENTO_MENSAGEM TEXT("EventoMensagem")
#define SHM_MENSAGEM TEXT("MemPartMensagem")
#define MENSAGEM_TXT TEXT("Mensagem")

#define MUTEX_JOGO TEXT("MutexJogo")
#define EVENTO_JOGO TEXT("EventoJogo")
#define SHM_JOGO TEXT("MemPartJogo")
#define JOGO_TXT TEXT("Jogo")

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	// Mémoria partilhada: Mensagens
	BRIDGE_API bool AcessoMensagensServidor(SincControl &sincControl);
	BRIDGE_API bool AcessoMensagensCliente(SincControl &sincControl);

	// Mémoria partilhada: Mensagen
	BRIDGE_API bool AcessoJogoServidor(SincControl &sincControl);
	BRIDGE_API bool AcessoJogoCliente(SincControl &sincControl);

	// utils.cpp
	BRIDGE_API void gotoxy(int x, int y);
	BRIDGE_API void closeSincControl(SincControl &sincControl);
}