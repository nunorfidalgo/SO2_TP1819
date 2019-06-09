#pragma once

// Sincronização e memoria partilha
typedef struct {

	HANDLE hMemMensagem;
	HANDLE hMutexMensagem;
	HANDLE hEventoMensagem;

	HANDLE hMemJogo;
	HANDLE hMutexJogo;
	HANDLE hEventoJogo;

	/* waitableTimer */
	SYSTEMTIME time;
	FILETIME ftime;
	HANDLE hTimer;

	/* memoria partilhada*/
	MENSAGEM* mensagem;
	JOGO* jogo;

} SincControl;