#pragma once

// Sincroniza��o
typedef struct {
	HANDLE hMemMensagem;
	HANDLE hMutexMensagem;
	HANDLE hEventoMensagem;
	HANDLE hMemJogo;
	HANDLE hMutexJogo;
	HANDLE hEventoJogo;
	MENSAGEM *mensagem;
	JOGO *jogo;
	/*int termina_mensagem;
	int termina_jogo;*/
} SincControl;