#pragma once
#define N_PIPES 4

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

/* named pipes */

typedef struct {

	HANDLE hInstance;

	OVERLAPPED overlap;

	BOOL activo;

} PIPEDATA;



typedef struct {

	PIPEDATA hPipes[N_PIPES];
	HANDLE hEvent[N_PIPES];
	HANDLE hMutex;
	DWORD pipeNumber;
	DWORD nBytesRecebidos;
	DWORD nBytesEnviados;
	int termina = 0;
	int numClientes = 0;

} SincPipes;