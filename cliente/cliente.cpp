#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

#include "../bridge/bridge.h"

// tamanho padrão da linha de comandos do windows
#define COLUNAS 80 // x
#define LINHAS 26 // y

#define SERVIDOR TEXT("Cliente:")

int _tmain(int argc, LPTSTR argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	_tprintf(TEXT("%s iniciou...\n"), SERVIDOR);
	AcedeMemoriaPartilhadaJogo();

	_tprintf(TEXT("%s teste de ção...\n"), SERVIDOR);

	system("cls");

	for (int x = 0; x < COLUNAS; x++) {
		gotoxy(x, 0);
		_tprintf(TEXT("-"));
		gotoxy(x, LINHAS + 1);
		_tprintf(TEXT("-"));
	}
	for (int y = 0; y <= LINHAS + 1; y++) {
		gotoxy(0, y);
		_tprintf(TEXT("|"));
		gotoxy(COLUNAS, y);
		_tprintf(TEXT("|"));
	}

	int x = COLUNAS / 2;
	int y = LINHAS - 1;
	gotoxy(x, y);
	_tprintf(TEXT("*"));

	int xd = 1 * 1;
	int yd = 1 * 1;

	while (1) {
		gotoxy(x, y);
		_tprintf(TEXT(" "));

		x += xd;
		y += yd;

		if (x > COLUNAS - 2 || x < 2) {
			xd *= 1 * -1;
		}

		if (y >= LINHAS || y < 2) {
			yd *= 1 * -1;
		}
		gotoxy(x, y);
		_tprintf(TEXT("*"));
		Sleep(20);
	}
	//gotoxy(COLUNAS + 1, LINHAS + 1);
	gotoxy(0, LINHAS + 1);


	//_gettchar();

	return 0;
}
