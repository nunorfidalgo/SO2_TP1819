#pragma once

#include "jogo.h"

// Mensagem
typedef struct {
	TCHAR nome[TEXTO];
	int bolax, bolay;
	int jogadorx, jogadory;
} MENSAGEM;

// Sincronização
typedef struct {
	HANDLE hMemMensagem;
	HANDLE hMutexMensagem;
	HANDLE hEventoMensagem;
	HANDLE hMemJogo;
	HANDLE hMutexJogo;
	HANDLE hEventoJogo;
	MENSAGEM *mensagem;
	JOGO *jogo;
	int termina_mensagem;
	int termina_jogo;
} SincControl;