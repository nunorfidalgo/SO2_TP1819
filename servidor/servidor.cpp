#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"

// posição inicial da bola
//int x = COLUNAS / 2, y = LINHAS - 1;
//int xa = x, ya = y;
//int xd = 1, yd = 1; // direcção
BOLA bola;

SincControl sincControl;

HANDLE hServidor;
HANDLE hTMensagens, hTJogo, hTBola;

bool verificaInstancia();
DWORD WINAPI recebeMensagens(LPVOID param);
DWORD WINAPI enviaJogo(LPVOID param);
DWORD WINAPI threadBola(LPVOID param);

int _tmain(int argc, LPTSTR argv[])
{

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("%s iniciou...\n"), SERVIDOR);

	if (verificaInstancia())
		return -1;

	if (!AcessoMensagensServidor(sincControl))
		return -1;

	if (!AcessoJogoServidor(sincControl))
		return -1;

	hTMensagens = CreateThread(NULL, 0, recebeMensagens, NULL, 0, NULL);

	hTJogo = CreateThread(NULL, 0, enviaJogo, NULL, 0, NULL);

	if (hTMensagens == NULL || hTJogo == NULL) {
		_tprintf(TEXT("%s Erro ao criar as threads da de recebeMensagens e enviaJogo\n"), SERVIDOR);
		return -1;
	}


	hTBola = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadBola, NULL, 0, NULL);

	if (hTBola == NULL) {
		_tprintf(TEXT("Erro ao criar as threads da bola e teclas\n"));
		return -1;
	}

	if (WaitForSingleObject(hTBola, INFINITE))
		return -1;

	if (WaitForSingleObject(hTMensagens, INFINITE) || (WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		_tprintf(TEXT("%s wait stop\n"), SERVIDOR);
		return -1;
	}

	closeSincControl(sincControl);
	CloseHandle(hTMensagens);
	CloseHandle(hTJogo);
	CloseHandle(hTBola);
	CloseHandle(hServidor);
	return 0;
}

bool verificaInstancia() {
	hServidor = CreateEventW(NULL, TRUE, FALSE, SERVIDOR);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hServidor);
		hServidor = NULL;
		_tprintf(TEXT("%s: Já exite uma instância do servidor a correr\n"), SERVIDOR);
		return true;
	}
	// the only instance, start in a usual way
	return false;
}

DWORD WINAPI recebeMensagens(LPVOID param) {
	_tprintf(TEXT("termina msg: %d\n"), sincControl.mensagem->termina);
	while (1)
	{
		if (sincControl.mensagem->termina == 1) exit(1);

		WaitForSingleObject(sincControl.hEventoMensagem, INFINITE);
		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		_tprintf(TEXT("Recebi Mensagem: '%s'=(%d,%d)\n"), sincControl.mensagem->nome, sincControl.mensagem->jogador.barreira.coord.x, sincControl.mensagem->jogador.barreira.coord.y);
		_tcscpy_s(sincControl.jogo->jogador.nome, sincControl.mensagem->nome);
		sincControl.jogo->jogador.barreira.coord.x = sincControl.mensagem->jogador.barreira.coord.x;
		sincControl.jogo->jogador.barreira.coord.y = sincControl.mensagem->jogador.barreira.coord.y;

		ReleaseMutex(sincControl.hMutexMensagem);
		Sleep(500);
	}
	return 0;
}

DWORD WINAPI enviaJogo(LPVOID param) {
	_tprintf(TEXT("termina jogo: %d\n"), sincControl.jogo->termina);
	int i = 1;

	_tprintf(TEXT("espero 8s...\n"));
	Sleep(8000);

	while (1) {
		if (sincControl.jogo->termina == 1) exit(1);
		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

		//sincControl.jogo->bola.coordAnt.x = xa;
		//sincControl.jogo->bola.coordAnt.y = ya;
		//sincControl.jogo->bola.coord.x = x;
		//sincControl.jogo->bola.coord.y = y;

		sincControl.jogo->bola.coordAnt.x = bola.coordAnt.x;
		sincControl.jogo->bola.coordAnt.y = bola.coordAnt.y;
		sincControl.jogo->bola.coord.x = bola.coord.x;
		sincControl.jogo->bola.coord.y = bola.coord.y;

		//CopyMemory(sincControl.jogo, &jogo, sizeof(JOGO));
		_tprintf(TEXT("[%d] Envio Jogo: '%s' (x,y)=(%d, %d) | Bola (x,y)=(%d, %d)\n"), i, sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
		i++;

		SetEvent(sincControl.hEventoJogo);
		ReleaseMutex(sincControl.hMutexJogo);
		ResetEvent(sincControl.hEventoJogo);

		Sleep(100);
	}
	return 0;
}

DWORD WINAPI threadBola(LPVOID param) {
	// posição inicial da bola
	//int x = COLUNAS / 2, y = LINHAS - 1;
	//int xa = x, ya = y;
	//int xd = 1, yd = 1; // direcção
	bola.coord.x = COLUNAS / 2;
	bola.coord.y = LINHAS - 1;
	bola.coordAnt.x = bola.coord.x;
	bola.coordAnt.y = bola.coord.y;
	bola.direcao.x = 1;
	bola.direcao.y = 1;

	while (1) {
		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);
		/*xa = x;
		ya = y;
		x -= xd;
		y -= yd;*/
		bola.coordAnt.x = bola.coord.x;
		bola.coordAnt.y = bola.coord.y;
		bola.coord.x -= bola.direcao.x;
		bola.coord.y = bola.direcao.y;

		if (bola.coord.x > COLUNAS - 2 || bola.coord.x < 2) { // limites direita e esquerda
			//xd *= -1;
			bola.direcao.x *= -1;
		}
		if (bola.coord.y > LINHAS || bola.coord.y < 2) { // limites inferior e superior
		//if (y < 2) { // limites superior
			//yd *= -1;
			bola.direcao.y *= -1;
		}

		/*if (y > LINHAS) {
			gotoxy(0, LINHAS + 2);
			_tprintf(TEXT("Perdeu o jogo..."));
			exit(1);
		}*/

		// barreira
		//if (y >= LINHAS) // limites inferior
		//	if (x >= xp && x <= xp + 5)
		//		yd *= -1;
		//	else {
		//		gotoxy(0, LINHAS + 2);
		//		_tprintf(TEXT("Perdeu o jogo...\n"));
		//		exit(1);
		//	}
		ReleaseMutex(sincControl.hMutexJogo);
		Sleep(80);
	}
}

