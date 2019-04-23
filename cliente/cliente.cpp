#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "../bridge/bridge.h"

// tamanho padrão da linha de comandos do windows
#define COLUNAS 81 // x
#define LINHAS 26 // y

#define SERVIDOR TEXT("Cliente:")

int _tmain(int argc, LPTSTR argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	int x, y;

	_tprintf(TEXT("%s iniciou...\n"), SERVIDOR);
	AcedeMemoriaPartilhadaJogo();

	_tprintf(TEXT("%s teste de ção...\n"), SERVIDOR);

	system("cls");
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
	_tprintf(TEXT("ESC - sair"));

	// posição inicial da bola
	x = COLUNAS / 2, y = LINHAS;
	int xd = 1, yd = 1;
	gotoxy(x, y);
	_tprintf(TEXT("*"));

	// barreira do jogador, posição inicial da barreira
	int xp = 1, yp = LINHAS, xpa = 0;
	gotoxy(xp, yp);
	_tprintf(TEXT("_____"));

	// teclas
	char key_input;

	while (1) {
		// apaga a posição anterior
		gotoxy(x, y);
		_tprintf(TEXT(" "));
		x -= xd;
		y -= yd;
		if (x > COLUNAS - 2 || x < 2) { // limites direita e esquerda
			xd *= -1;
		}
		if (y >= LINHAS || y < 2) { // limites inferior e superior
			yd *= -1;
		}
		gotoxy(x, y);
		_tprintf(TEXT("*"));

		if (_kbhit()) {
			key_input = _gettch();
			key_input = toupper(key_input);
			_flushall();
			//fflush(stdin);
			switch (key_input) {
			case 77: //direta
				if (xp < COLUNAS - 5) {
					xpa = xp;
					xp += 5;
					gotoxy(xpa, yp);
					_tprintf(TEXT("     "));
					gotoxy(xp, yp);
					_tprintf(TEXT("_____"));
				}
				break;
			case 75: // esquerda
				if (xp > 1) {
					xpa = xp;
					xp -= 5;
					gotoxy(xpa, yp);
					_tprintf(TEXT("     "));
					gotoxy(xp, yp);
					_tprintf(TEXT("_____"));
				}
				break;
			case 27: // ESC = sair
				gotoxy(0, LINHAS + 2);
				exit(1);
				break;
			}
		}
		gotoxy(COLUNAS + 3, 1);
		_tprintf(TEXT("                         "));
		gotoxy(COLUNAS + 3, 1);
		_tprintf(TEXT("Bola (x,y) = (%.2d, %.2d)"), x, y);
		gotoxy(COLUNAS + 3, 2);
		_tprintf(TEXT("                         "));
		gotoxy(COLUNAS + 3, 2);
		_tprintf(TEXT("Bola (xd,yd) = (%d, %d)"), xd, yd);
		gotoxy(COLUNAS + 3, 3);
		_tprintf(TEXT("               "));
		gotoxy(COLUNAS + 3, 3);
		_tprintf(TEXT("Barreira = xp: %d, xpa: %d"), xp, xpa);
		Sleep(50);
	}
	gotoxy(0, LINHAS + 1);
	return 0;
}
