#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"

#define SHM_MENSAGENS TEXT("SHM_Mensagens")
#define MUTEX_MENSAGENS TEXT("MutexMensagens")
#define EVENTO_MENSAGENS TEXT("EventoMensagens")
HANDLE hMuMensagens;
HANDLE hEvMensagens;
HANDLE hMemMensagens;
MENSAGEM *mensagem;

#define SHM_JOGO TEXT("SHM_Jogo")
#define MUTEX_JOGO TEXT("MutexJogo")
#define EVENTO_JOGO TEXT("EventoJogo")
HANDLE hMuJogo;
HANDLE hEvJogo;
HANDLE hMemJogo;
JOGO *jogo;

HANDLE hTMensagens, hTJogo;

TCHAR nome[NOME];

DWORD WINAPI recebeMensagens(LPVOID param);
DWORD WINAPI enviaJogo(LPVOID param);

int _tmain(int argc, LPTSTR argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	system("cls");
	_tprintf(TEXT("%s iniciou...\n"), SERVIDOR);


	/*hMuMensagens = CreateMutex(NULL, FALSE, MUTEX_MENSAGENS);
	hEvMensagens = CreateEvent(NULL, TRUE, FALSE, EVENTO_MENSAGENS);
	hMemMensagens = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(MENSAGEM), SHM_MENSAGENS);
	if (hMuMensagens == NULL || hEvMensagens == NULL || hMemMensagens == NULL) {
		_tprintf(TEXT("[Erro]Criação de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	mensagem = (MENSAGEM*)MapViewOfFile(hMemMensagens, FILE_MAP_READ, 0, 0, sizeof(MENSAGEM));
	if (mensagem == NULL) {
		_tprintf(TEXT("[Erro]Mapeamento da memória partilhada(%d)\n"), GetLastError());
		return -1;
	}*/



	hMuJogo = CreateMutex(NULL, FALSE, MUTEX_JOGO);
	hEvJogo = CreateEvent(NULL, TRUE, FALSE, EVENTO_JOGO);

	hMemJogo = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(JOGO), SHM_JOGO);
	if (hMuJogo == NULL || hEvJogo == NULL || hMemJogo == NULL) {
		_tprintf(TEXT("[Erro] Criação de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	jogo = (JOGO*)MapViewOfFile(hMemJogo, FILE_MAP_WRITE, 0, 0, sizeof(JOGO));
	if (jogo == NULL) {
		_tprintf(TEXT("[Erro] Mapeamento da memória partilhada (%d)\n"), GetLastError());
		return -1;
	}

	/*hTMensagens = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)recebeMensagens, NULL, 0, NULL);*/
	hTJogo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enviaJogo, NULL, 0, NULL);

	if (/*hTMensagens == NULL && */hTJogo == NULL)
		_tprintf(TEXT("Erro ao criar as threads da de recebeMensagens e enviaJogo\n"));

	if (/*WaitForSingleObject(hTMensagens, INFINITE) ||*/ (WaitForSingleObject(hTJogo, INFINITE)) == NULL)
		return -1;

	UnmapViewOfFile(mensagem);
	UnmapViewOfFile(jogo);
	CloseHandle(hMuMensagens);
	CloseHandle(hMuJogo);
	CloseHandle(hEvMensagens);
	CloseHandle(hEvJogo);
	CloseHandle(hMemMensagens);
	CloseHandle(hMemJogo);

	return 0;
}

DWORD WINAPI recebeMensagens(LPVOID param) {
	while (1)
	{
		_tprintf(TEXT("Aguardo mensagem...\n"));

		WaitForSingleObject(hEvMensagens, INFINITE);
		WaitForSingleObject(hMuMensagens, INFINITE);

		_tprintf(TEXT("Recebi Mensagem: '%s'=(%d,%d) | Bola=(%d,%d)\n"), mensagem->nome, mensagem->jogadorx, mensagem->jogadory, mensagem->bolax, mensagem->bolay);

		ReleaseMutex(hMuMensagens);
	}
}

DWORD WINAPI enviaJogo(LPVOID param) {
	int i = 1;
	while (1)
	{
		WaitForSingleObject(hMuJogo, INFINITE);

		_stprintf_s(nome, sizeof(nome), TEXT("Teste do jogo %d"), i);
		_tcscpy_s(jogo->nome, sizeof(nome), nome);
		/*mensagem->bolax = i;
		mensagem->bolay = i;
		mensagem->jogadorx = i;
		mensagem->jogadory = i;*/
		i++;
		_tprintf(TEXT("Envio Jogo: '%s'\n"), jogo->nome);

		SetEvent(hEvJogo);
		ReleaseMutex(hMuJogo);
		ResetEvent(hEvJogo);

		Sleep(2000);
	}
}
