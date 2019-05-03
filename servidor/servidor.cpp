#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"

TCHAR nome[TEXTO];
SincControl sincControl;

HANDLE hTMensagens, hTJogo;

DWORD WINAPI recebeMensagens(LPVOID param);
DWORD WINAPI enviaJogo(LPVOID param);

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
	sincControl.hEventoMensagem = CreateEvent(NULL, TRUE, FALSE, EVENTO_MENSAGEM);
	sincControl.hMemMensagem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(MENSAGEM), SHM_MENSAGEM);
	sincControl.mensagem = (MENSAGEM*)MapViewOfFile(sincControl.hMemMensagem, FILE_MAP_READ, 0, 0, sizeof(MENSAGEM));
	if (sincControl.mensagem == NULL) {
		_tprintf(TEXT("[Erro: %s] Mapeamento da memória partilhada (%d)\n"), MENSAGEM_TXT, GetLastError());
		return -1;
	}
	if (sincControl.hMemMensagem == NULL || sincControl.hMutexMensagem == NULL || sincControl.hEventoMensagem == NULL) {
		_tprintf(TEXT("[Erro: %s] Criação de objectos (%d)\n"), MENSAGEM_TXT, GetLastError());
		return -1;
	}

	sincControl.hMutexJogo = CreateMutex(NULL, FALSE, MUTEX_JOGO);
	sincControl.hEventoJogo = CreateEvent(NULL, TRUE, FALSE, EVENTO_JOGO);
	sincControl.hMemJogo = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(JOGO), SHM_JOGO);
	if (sincControl.hMutexJogo == NULL || sincControl.hEventoJogo == NULL || sincControl.hMemJogo == NULL) {
		_tprintf(TEXT("[Erro: %s] Criação de objectos (%d)\n"), JOGO_TXT, GetLastError());
		return -1;
	}
	sincControl.jogo = (JOGO*)MapViewOfFile(sincControl.hMemJogo, FILE_MAP_WRITE, 0, 0, sizeof(JOGO));
	if (sincControl.jogo == NULL) {
		_tprintf(TEXT("[Erro %s] Mapeamento da memória partilhada (%d)\n"), JOGO_TXT, GetLastError());
		return -1;
	}


	hTMensagens = CreateThread(NULL, 0, recebeMensagens, NULL, 0, NULL);
	hTJogo = CreateThread(NULL, 0, enviaJogo, NULL, 0, NULL);

	if (hTMensagens == NULL || hTJogo == NULL) {
		_tprintf(TEXT("%s Erro ao criar as threads da de recebeMensagens e enviaJogo\n"), SERVIDOR);
		return -1;
	}

	if (WaitForSingleObject(hTMensagens, INFINITE) || (WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		_tprintf(TEXT("%s wait stop\n"), SERVIDOR);
		return -1;
	}

	CloseHandle(sincControl.hMutexMensagem);
	CloseHandle(sincControl.hEventoMensagem);
	CloseHandle(sincControl.hMutexJogo);
	CloseHandle(sincControl.hEventoJogo);
	UnmapViewOfFile(sincControl.mensagem);
	UnmapViewOfFile(sincControl.jogo);
	CloseHandle(sincControl.hMemMensagem);
	CloseHandle(sincControl.hMemJogo);
	CloseHandle(hTMensagens);
	CloseHandle(hTJogo);
	return 0;
}

DWORD WINAPI recebeMensagens(LPVOID param) {
	while (1)
	{
		_tprintf(TEXT("Aguardo mensagem: "));

		WaitForSingleObject(sincControl.hEventoMensagem, INFINITE);
		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		_tprintf(TEXT("Recebi Mensagem: '%s'=(%d,%d) | Bola=(%d,%d)\n"), sincControl.mensagem->nome, sincControl.mensagem->jogadorx, sincControl.mensagem->jogadory, sincControl.mensagem->bolax, sincControl.mensagem->bolay);

		ReleaseMutex(sincControl.hMutexMensagem);
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI enviaJogo(LPVOID param) {
	_tprintf(TEXT("%s enviaJogo\n"), SERVIDOR);
	int i = 1;
	JOGO jogo;
	while (1)
	{
		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

		_stprintf_s(jogo.jogador.nome, TEXTO, TEXT("Teste do jogo %d"), i);
		/*_tcscpy_s(jogo.jogador.nome, nome);*/
		jogo.bola.coord.x = i;
		jogo.bola.coord.y = i;
		jogo.jogador.barreira.coord.x = i;
		jogo.jogador.barreira.coord.y = i;
		//_tprintf(TEXT("Envio Jogo: '%s' = (%d,%d) | Bola = (%d,%d)\n"), jogo.jogador.nome, jogo.jogador.barreira.coord.x, jogo.jogador.barreira.coord.y, jogo.bola.coord.x, jogo.bola.coord.y);

		CopyMemory(sincControl.jogo, &jogo, sizeof(JOGO));
		_tprintf(TEXT("[%d] Envio Jogo: '%s' = (%d, %d) | Bola = (%d, %d)\n"), i, sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
		i++;

		SetEvent(sincControl.hEventoJogo);
		ReleaseMutex(sincControl.hMutexJogo);
		ResetEvent(sincControl.hEventoJogo);

		Sleep(1000);
	}
	return 0;
}
