#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"

TCHAR nome[TEXTO];
SincControl sincControl;

HANDLE hTMensagens; // , hTJogo;

DWORD WINAPI recebeMensagens(LPVOID param);
//DWORD WINAPI enviaJogo(LPVOID param);

int _tmain(int argc, LPTSTR argv[])
{

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("%s iniciou...\n"), SERVIDOR);

	sincControl.hMutexMensagem = CreateMutex(NULL, FALSE, MUTEX_MENSAGEM);
	//_tprintf(TEXT("%s CreateMutex\n"), SERVIDOR);

	sincControl.hEventoMensagem = CreateEvent(NULL, TRUE, FALSE, EVENTO_MENSAGEM);
	//_tprintf(TEXT("%s CreateEvent\n"), SERVIDOR);

	sincControl.hMemMensagem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(MENSAGEM), SHM_MENSAGEM);
	//_tprintf(TEXT("%s CreateFileMapping\n"), SERVIDOR);

	sincControl.mensagem = (MENSAGEM*)MapViewOfFile(sincControl.hMemMensagem, FILE_MAP_READ, 0, 0, sizeof(MENSAGEM));
	if (sincControl.mensagem == NULL) {
		_tprintf(TEXT("[Erro: %s] Mapeamento da memória partilhada (%d)\n"), TEXT("Mensagem"), GetLastError());
		return -1;
	}
	//_tprintf(TEXT("%s MapViewOfFile\n"), SERVIDOR);

	if (sincControl.hMemMensagem == NULL || sincControl.hMutexMensagem == NULL || sincControl.hEventoMensagem == NULL) {
		_tprintf(TEXT("[Erro: %s] Criação de objectos (%d)\n"), TEXT("Mensagem"), GetLastError());
		return -1;
	}
	//_tprintf(TEXT("%s erros...\n"), SERVIDOR);


	/*hMemJogo = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(JOGO), SHM_JOGO);
	jogo->hMutexJogo = CreateMutex(NULL, FALSE, MUTEX_JOGO);
	jogo->hEventoJogo = CreateEvent(NULL, TRUE, FALSE, EVENTO_JOGO);
	if (jogo->hMutexJogo == NULL || jogo->hEventoJogo == NULL || hMemJogo == NULL) {
		_tprintf(TEXT("[Erro: %s] Criação de objectos (%d)\n"), TEXT("Jogo"), GetLastError());
		return -1;
	}
	jogo = (JOGO*)MapViewOfFile(hMemJogo, FILE_MAP_WRITE, 0, 0, sizeof(JOGO));
	if (jogo == NULL) {
		_tprintf(TEXT("[Erro %s] Mapeamento da memória partilhada (%d)\n"), TEXT("Jogo"), GetLastError());
		return -1;
	}
*/


//_tprintf(TEXT("%s CreateThread\n"), SERVIDOR);
	hTMensagens = CreateThread(NULL, 0, recebeMensagens, NULL, 0, NULL);
	//hTJogo = CreateThread(NULL, 0, enviaJogo, NULL, 0, NULL);

	if (hTMensagens == NULL /*|| hTJogo == NULL*/) {
		_tprintf(TEXT("%s Erro ao criar as threads da de recebeMensagens e enviaJogo\n"), SERVIDOR);
		return -1;
	}

	if (WaitForSingleObject(hTMensagens, INFINITE) /*|| (WaitForSingleObject(hTJogo, INFINITE)) == NULL*/) {
		_tprintf(TEXT("%s wait stop\n"), SERVIDOR);
		return -1;
	}

	CloseHandle(sincControl.hMutexMensagem);
	CloseHandle(sincControl.hEventoMensagem);
	UnmapViewOfFile(sincControl.mensagem);
	UnmapViewOfFile(sincControl.jogo);
	CloseHandle(sincControl.hMemMensagem);
	CloseHandle(sincControl.hMemJogo);
	CloseHandle(hTMensagens);
	//CloseHandle(hTJogo);
	return 0;
}

DWORD WINAPI recebeMensagens(LPVOID param) {
	//_tprintf(TEXT("%s recebeMensagens\n"), SERVIDOR);
	while (1)
	{
		_tprintf(TEXT("Aguardo mensagem...\n"));

		WaitForSingleObject(sincControl.hEventoMensagem, INFINITE);
		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		_tprintf(TEXT("Recebi Mensagem: '%s'=(%d,%d) | Bola=(%d,%d)\n"), sincControl.mensagem->nome, sincControl.mensagem->jogadorx, sincControl.mensagem->jogadory, sincControl.mensagem->bolax, sincControl.mensagem->bolay);

		ReleaseMutex(sincControl.hMutexMensagem);
	}
	return 0;
}
//
//DWORD WINAPI enviaJogo(LPVOID param) {
//	_tprintf(TEXT("%s enviaJogo\n"), SERVIDOR);
//	int i = 1;
//	while (1)
//	{
//		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);
//
//		_stprintf_s(nome, TEXTO, TEXT("Teste do jogo %d"), i);
//		_tcscpy_s(sincControl.jogo->nome, nome);
//
//		/*mensagem->bolax = i;
//		mensagem->bolay = i;
//		mensagem->jogadorx = i;
//		mensagem->jogadory = i;*/
//
//		i++;
//		_tprintf(TEXT("Envio Jogo: '%s'\n"), sincControl.jogo->nome);
//
//		SetEvent(sincControl.hEventoJogo);
//		ReleaseMutex(sincControl.hMutexJogo);
//		ResetEvent(sincControl.hEventoJogo);
//
//		Sleep(2000);
//	}
//	return 0;
//}
