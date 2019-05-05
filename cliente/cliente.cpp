//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_NON_CONFORMING_SWPRINTFS
//#define UNICODE
//#define _UNICODE

#include <Windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "../bridge/bridge.h"

JOGADOR jogador;
SincControl sincControl;

HANDLE hLogin;
HANDLE htTeclas, hTMensagens, hTJogo;
DWORD hTMensagensId, hTJogoId, htTeclasId;

void entrar();
void imprimeJogo();
DWORD WINAPI envioMensagem(LPVOID param);
DWORD WINAPI recebeJogo(LPVOID param);
DWORD WINAPI threadTeclas(LPVOID param);

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("%s: Pronto...\n"), CLIENTE);

	if (!AcessoMensagensCliente(sincControl)) {
		return -1;
	}

	if (!AcessoJogoCliente(sincControl)) {
		return -1;
	}

	hLogin = OpenEvent(FILE_MAP_WRITE, FALSE, TEXT("LOGIN"));
	if (hLogin == NULL) {
		_tprintf(TEXT("%s: [ERRO] Criação evento do login (%d)\n"), CLIENTE, GetLastError());
		exit(-1);
	}
	entrar();
	SetEvent(hLogin);
	ResetEvent(hLogin);
	CloseHandle(hLogin);

	imprimeJogo();

	hTMensagens = CreateThread(NULL, 0, envioMensagem, NULL, 0, &hTMensagensId);
	if (hTMensagens == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
		return -1;
	}

	hTJogo = CreateThread(NULL, 0, recebeJogo, NULL, 0, &hTJogoId);
	if (hTJogo == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
		return -1;
	}

	htTeclas = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTeclas, NULL, 0, &htTeclasId);
	if (htTeclas == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das teclas...\n"), CLIENTE, GetLastError(), htTeclasId);
		return -1;
	}

	if (WaitForSingleObject(hTMensagens, INFINITE)) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
		//return -1;
	}
	if ((WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
		//return -1;
	}
	if ((WaitForSingleObject(htTeclas, INFINITE)) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das teclas...\n"), CLIENTE, GetLastError(), htTeclasId);
		//return -1;
	}

	_tprintf(TEXT("%s: [LastError %d] terminou...\n"), CLIENTE, GetLastError());

	closeSincControl(sincControl);
	CloseHandle(hTMensagens);
	CloseHandle(hTJogo);
	CloseHandle(htTeclas);
	return 0;
}

DWORD WINAPI envioMensagem(LPVOID param) {
	while (true) {
		//while (!sincControl.mensagem->termina) {

		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		_tcscpy_s(sincControl.mensagem->jogador.nome, jogador.nome);
		sincControl.mensagem->jogador.barreira.coord.x = jogador.barreira.coord.x;
		sincControl.mensagem->jogador.barreira.coord.y = jogador.barreira.coord.y;

		//debug
		//_tprintf(TEXT("[Thread: %d] Envio Mensagem: Jogador: '%s'=(%d,%d) | termina: %d\n"), GetCurrentThreadId(), sincControl.mensagem->jogador.nome, sincControl.mensagem->jogador.barreira.coord.x, sincControl.mensagem->jogador.barreira.coord.y, sincControl.mensagem->termina);

		SetEvent(sincControl.hEventoMensagem);
		ReleaseMutex(sincControl.hMutexMensagem);
		ResetEvent(sincControl.hEventoMensagem);

		Sleep(VEL_JOGO);
	}
	return 0;
}

DWORD WINAPI recebeJogo(LPVOID param) {
	while (true) { // !sincControl.jogo->termina
	//while (!sincControl.jogo->termina) {

		WaitForSingleObject(sincControl.hEventoJogo, INFINITE);
		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

		gotoxy(sincControl.jogo->bola.coordAnt.x, sincControl.jogo->bola.coordAnt.y);
		_tprintf(TEXT(" "));
		gotoxy(sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
		_tprintf(TEXT("*"));

		//limpa a barreira canto esquerdo
		gotoxy(1, LINHAS);
		_tprintf(TEXT("                                        ")); //nao apagar isto

		// limpar a posição anteriro não esta a funcionar
		/*gotoxy(sincControl.jogo->jogador.barreira.coordAnt.x, LINHAS);
		_tprintf(TEXT("       "));*/

		gotoxy(sincControl.jogo->jogador.barreira.coord.x, LINHAS);
		_tprintf(TEXT("_____"));

		gotoxy(COLUNAS + 3, 2);
		_tprintf(TEXT("Jogador: %s"), sincControl.jogo->jogador.nome);
		gotoxy(COLUNAS + 3, 3);
		_tprintf(TEXT("Bola (x,y)=(%.2d, %.2d)"), sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
		gotoxy(COLUNAS + 3, 4);
		_tprintf(TEXT("Barreira (xp, yp)=(%.2d, %.2d)"), sincControl.jogo->jogador.barreira.coord.x, LINHAS);

		//if (sincControl.jogo->termina == 1) exit(1);

		ReleaseMutex(sincControl.hMutexJogo);

		// debug
		/*_tprintf(TEXT("[Thread: %d] Recebo Jogo: Jogador: '%s' (x,y)=(%d, %d) | Bola (x,y)=(%d, %d) | termina: %d\n"), GetCurrentThreadId(), sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, sincControl.jogo->termina);
		Sleep(VEL_JOGO);*/

	}
	return 0;
}

// Login
void entrar() {
	TCHAR nome[TEXTO];
	_tprintf(TEXT("Nome jogador: "));
	_getts_s(nome);
	_tcscpy_s(jogador.nome, nome);
	_tprintf(TEXT("O jogo vai começar '%s'... carregue numa tecla para continuar...\n"), jogador.nome);
	_gettch();
}

void imprimeJogo() {
	system("cls");
	int x, y;
	// Limites do jogo
	for (x = 0; x < COLUNAS; x++) {
		gotoxy(x, 0);
		_tprintf(TEXT("-"));
		gotoxy(x, LINHAS + 1);
		_tprintf(TEXT("-"));
	}

	for (y = 0; y <= LINHAS + 1; y++) {
		gotoxy(0, y);
		_tprintf(TEXT("|"));
		gotoxy(COLUNAS, y);
		_tprintf(TEXT("|"));
	}

	// Tijolos
	for (y = 4; y < 7; y++)
		for (x = 6; x < COLUNAS - 6; x++) {
			gotoxy(x, y);
			_tprintf(TEXT("#"));
		}

	for (y = 8; y < 11; y++)
		for (x = 6; x < COLUNAS - 6; x++) {
			gotoxy(x, y);
			_tprintf(TEXT("&"));
		}

	gotoxy(COLUNAS + 3, 0);
	_tprintf(TEXT("-------------- ARKNOID / BREAKOUT------------\n"));
	gotoxy(COLUNAS + 3, 24);
	_tprintf(TEXT("ESC - sair"));
}

DWORD WINAPI threadTeclas(LPVOID param) {
	// barreira do jogador, posição inicial da barreira e posição anterior
	jogador.barreira.coord.x = 1;
	jogador.barreira.coord.y = LINHAS;
	TCHAR key_input;
	while (true) { //!sincControl.jogo->termina
	//while (!sincControl.jogo->termina) {
		key_input = _gettch();
		key_input = toupper(key_input);
		_flushall();
		switch (key_input) {
		case 77: //direta
			if (jogador.barreira.coord.x < COLUNAS - 5) {
				jogador.barreira.coord.x += 5;
			}
			break;
		case 75: // esquerda
			if (jogador.barreira.coord.x > 1) {
				jogador.barreira.coord.x -= 5;
			}
			break;
		case 27: // ESC = sair
			//system("cls");
			sincControl.mensagem->termina = 1;
			//sincControl.jogo->termina = 1;
			gotoxy(0, LINHAS + 2);
			_tprintf(TEXT("Jogador cancelou do jogo..."));
			Sleep(1000);
			exit(1);
			break;
		}
		return 0;
	}

}