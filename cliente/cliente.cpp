﻿//#define _CRT_SECURE_NO_WARNINGS
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

HANDLE htTeclas, hTMensagens, hTJogo;

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
	_tprintf(TEXT("%s iniciou...\n"), CLIENTE);

	if (!AcessoMensagensCliente(sincControl)) {
		return -1;
	}

	entrar();

	if (!AcessoJogoCliente(sincControl)) {
		return -1;
	}

	imprimeJogo();

	hTMensagens = CreateThread(NULL, 0, envioMensagem, NULL, 0, NULL);
	hTJogo = CreateThread(NULL, 0, recebeJogo, NULL, 0, NULL);

	if (hTMensagens == NULL || hTJogo == NULL) {
		_tprintf(TEXT("%s Erro ao criar as threads da de recebeMensagens e enviaJogo\n"), CLIENTE);
		return -1;
	}

	htTeclas = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTeclas, NULL, 0, NULL);

	if (htTeclas == NULL) {
		_tprintf(TEXT("Erro ao criar as threads teclas\n"));
		return -1;
	}

	if ((WaitForSingleObject(htTeclas, INFINITE)) == NULL)
		return -1;

	if (WaitForSingleObject(hTMensagens, INFINITE) || (WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		_tprintf(TEXT("%s wait stop\n"), CLIENTE);
		return -1;
	}

	closeSincControl(sincControl);
	CloseHandle(hTMensagens);
	CloseHandle(hTJogo);
	CloseHandle(htTeclas);
	return 0;
}

DWORD WINAPI envioMensagem(LPVOID param) {
	while (1)
	{
		if (sincControl.mensagem->termina == 1) exit(1);

		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		//sincControl.mensagem->coord.x = xp;
		//sincControl.mensagem->coord.y = LINHAS;
		sincControl.mensagem->jogador.barreira.coord.x = jogador.barreira.coord.x;
		sincControl.mensagem->jogador.barreira.coord.y = jogador.barreira.coord.y;

		SetEvent(sincControl.hEventoMensagem);
		ReleaseMutex(sincControl.hMutexMensagem);
		ResetEvent(sincControl.hEventoMensagem);

	}
	return 0;
}

DWORD WINAPI recebeJogo(LPVOID param) {
	while (1)
	{
		if (sincControl.jogo->termina == 1) exit(1);

		WaitForSingleObject(sincControl.hEventoJogo, INFINITE);
		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

		gotoxy(sincControl.jogo->bola.coordAnt.x, sincControl.jogo->bola.coordAnt.y);
		_tprintf(TEXT(" "));
		gotoxy(sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
		_tprintf(TEXT("*"));

		gotoxy(sincControl.jogo->jogador.barreira.coordAnt.x, LINHAS);
		_tprintf(TEXT("       "));
		gotoxy(sincControl.jogo->jogador.barreira.coord.x, LINHAS);
		_tprintf(TEXT("_____"));

		gotoxy(COLUNAS + 3, 2);
		_tprintf(TEXT("Bola (x,y)=(%.2d, %.2d)"), sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
		gotoxy(COLUNAS + 3, 3);
		_tprintf(TEXT("Barreira (xp, yp)=(%.2d, %.2d)"), sincControl.jogo->jogador.barreira.coord.x, LINHAS);

		ReleaseMutex(sincControl.hMutexJogo);
	}
	return 0;
}

void entrar() {
	TCHAR nome[TEXTO];
	_tprintf(TEXT("Nome jogador: "));
	_getts_s(nome);
	_tcscpy_s(sincControl.mensagem->nome, nome);
	_tprintf(TEXT("O jogo vai começar '%s'... carregue numa tecla para continuar..."), sincControl.mensagem->nome);
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
	//int xp = 1, yp = LINHAS;
	jogador.barreira.coord.x = 1;
	jogador.barreira.coord.y = LINHAS;
	TCHAR key_input;
	while (1) {
		key_input = _gettch();
		key_input = toupper(key_input);
		_flushall();
		//fflush(stdin);
		switch (key_input) {
		case 77: //direta
			if (jogador.barreira.coord.x < COLUNAS - 5) {
				//xp += 5;
				jogador.barreira.coord.x += 5;
				/*sincControl.mensagem->jogadorx = xp;*/
			}
			break;
		case 75: // esquerda
			if (jogador.barreira.coord.x > 1) {
				//xp -= 5;
				jogador.barreira.coord.x -= 5;
				//sincControl.mensagem->jogadorx = xp;
			}
			break;
		case 27: // ESC = sair
			sincControl.mensagem->termina = 1;
			sincControl.jogo->termina = 1;
			gotoxy(0, LINHAS + 2);
			_tprintf(TEXT("Jogador cancelou do jogo..."));
			exit(1);
			break;
		}
	}

}