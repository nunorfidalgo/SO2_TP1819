#pragma once

#include <windows.h>
#include <tchar.h>
//#include <locale.h>
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

#define VEL_JOGO 5 // 5 mili segundos

#define MUTEX_MENSAGEM TEXT("MutexMensagem")
#define EVENTO_MENSAGEM TEXT("EventoMensagem")
#define SHM_MENSAGEM TEXT("MemPartMensagem")
#define MENSAGEM_TXT TEXT("Mensagem")

#define MUTEX_JOGO TEXT("MutexJogo")
#define EVENTO_JOGO TEXT("EventoJogo")
#define SHM_JOGO TEXT("MemPartJogo")
#define JOGO_TXT TEXT("Jogo")

#define LOGIN TEXT("Login")

#define JOGO_TIMER TEXT("WAITABLE_TIMER_SERVIDOR")


#define MUTEX_PIPES_MENSAGENS TEXT("MutexPipesMensagens")
#define PIPE_MENSAGENS TEXT("\\\\.\\pipe\\mensagens")

#define MUTEX_PIPES_JOGO TEXT("MutexPipeJogo")
#define PIPE_JOGO TEXT("\\\\.\\pipe\\jogo")

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	// Mémoria partilhada: memoria.cpp
	// Mensagens
	BRIDGE_API bool AcessoMensagensMemPartServidor(SincControl &sincControl);
	BRIDGE_API bool AcessoMensagensMemPartCliente(SincControl &sincControl);

	// Jogo
	BRIDGE_API bool AcessoJogoMemPartServidor(SincControl &sincControl);
	BRIDGE_API bool AcessoJogoMemPartCliente(SincControl &sincControl);

	// jogo.cpp
	BRIDGE_API void enviaJogoMemPart(SincControl &sincControl, BOLA &bola);
	BRIDGE_API void recebeJogoMemPart(SincControl &sincControl, BOLA &bola);
	BRIDGE_API void enviaJogoPipe(SincPipes &sincPipes, BOLA *bola);
	BRIDGE_API bool recebeJogoPipe(HANDLE hPipe, BOLA *bola);

	// mensagens.cpp
	BRIDGE_API void enviaMensagemMemPart(SincControl &sincControl, JOGADOR &jogador);
	BRIDGE_API void recebeMensagensMemPart(SincControl &sincControl);

	BRIDGE_API bool enviaMensagemPipe(HANDLE hPipe, MENSAGEM *mensagem);
	BRIDGE_API bool recebeMensagensPipes(SincPipes &sincPipes, MENSAGEM *mensagem);

	// utils.cpp
	BRIDGE_API void gotoxy(int x, int y);
	BRIDGE_API void closeSincControl(SincControl &sincControl);
	BRIDGE_API bool initWaitableTimer(SincControl &sincControl, JOGO &jogo);

	BRIDGE_API void Cleanup(PSID pEveryoneSID, PSID pAdminSID, PACL pACL, PSECURITY_DESCRIPTOR pSD);
	BRIDGE_API void Seguranca(SECURITY_ATTRIBUTES *sa);

	// pipes.cpp
	BRIDGE_API void escutaPipes(SincPipes &sincPipes);
	BRIDGE_API bool AcessoPipesMensagensServidor(SincPipes &sincPipes);
	BRIDGE_API bool AcessoPipeMensagensCliente(HANDLE &hPipe);
	BRIDGE_API bool AcessoPipesJogoServidor(SincPipes &sincPipes);
	BRIDGE_API bool AcessoPipesJogoCliente(HANDLE hPipe);
	BRIDGE_API void closePipes(SincPipes &sincPipes);

}