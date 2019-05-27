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
// consola
#define COLUNAS 41 // x
#define LINHAS 26 // y
// WDA
#define _WINDOW_WIDTH 450// x
#define _WINDOW_HEIGHT 600 // y

#define VEL_JOGO 50

#define MUTEX_MENSAGEM TEXT("MutexMensagem")
#define EVENTO_MENSAGEM TEXT("EventoMensagem")
#define SHM_MENSAGEM TEXT("MemPartMensagem")
#define MENSAGEM_TXT TEXT("Mensagem")

#define MUTEX_JOGO TEXT("MutexJogo")
#define EVENTO_JOGO TEXT("EventoJogo")
#define SHM_JOGO TEXT("MemPartJogo")
#define JOGO_TXT TEXT("Jogo")

#define LOGIN TEXT("LOGIN")

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	// Mémoria partilhada: memoria.cpp
	// Mensagens
	BRIDGE_API bool AcessoMensagensServidor(SincControl &sincControl);
	BRIDGE_API bool AcessoMensagensCliente(SincControl &sincControl);
	// Jogo
	BRIDGE_API bool AcessoJogoServidor(SincControl &sincControl);
	BRIDGE_API bool AcessoJogoCliente(SincControl &sincControl);

	// jogo.cpp
	BRIDGE_API void enviaJogo(SincControl &sincControl, BOLA &bola);
	BRIDGE_API void recebeJogo(SincControl &sincControl, BOLA &bola);

	// mensagens.cpp
	BRIDGE_API void enviaMensagem(SincControl &sincControl, JOGADOR &jogador);
	BRIDGE_API void recebeMensagens(SincControl &sincControl);

	// utils.cpp
	BRIDGE_API void gotoxy(int x, int y);
	BRIDGE_API void closeSincControl(SincControl &sincControl);
}