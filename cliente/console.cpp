#include "cliente.h"

extern JOGADOR jogador;

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