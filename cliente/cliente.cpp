#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "../bridge/bridge.h"

// tamanho padrão da linha de comandos do windows
#define COLUNAS 41 // x
#define LINHAS 26 // y

#define SERVIDOR TEXT("Cliente:")

HANDLE hMutex;
// posição inicial da bola
int x = COLUNAS / 2, y = LINHAS - 1;
int xd = 1, yd = 1;
int xp = 1, yp = LINHAS, xpa = xp;

DWORD WINAPI threadBola(LPVOID param);
DWORD WINAPI threadTeclas(LPVOID param);

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif
	int x, y;
	HANDLE hTBola, hTeclas;

	hMutex = CreateMutex(NULL, FALSE, NULL);
	if (hMutex == NULL) {
		_tprintf(TEXT("Erro ao criar mutex: %d\n"), GetLastError());
		return 1;
	}

	_tprintf(TEXT("%s iniciou...\n"), SERVIDOR);

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
	/*for (y = 4; y < 7; y++)
		for (x = 6; x < COLUNAS - 6; x++) {
			gotoxy(x, y);
			_tprintf(TEXT("#"));
		}

	for (y = 8; y < 11; y++)
		for (x = 6; x < COLUNAS - 6; x++) {
			gotoxy(x, y);
			_tprintf(TEXT("&"));
		}*/


	gotoxy(COLUNAS + 3, 0);
	_tprintf(TEXT("-------------- ARKNOID / BREAKOUT------------\n"));
	gotoxy(COLUNAS + 3, 2);
	AcedeMemoriaPartilhadaJogo();
	gotoxy(COLUNAS + 3, 26);
	_tprintf(TEXT("ESC - sair"));

	hTBola = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadBola, NULL, 0, NULL);
	hTeclas = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTeclas, NULL, 0, NULL);

	if (hTBola != NULL && hTeclas != NULL) {
		WaitForSingleObject(hMutex, INFINITE); //péssima solução usada com I / O
		gotoxy(COLUNAS + 3, 3);
		_tprintf(TEXT("Lancei as threads da bola e das teclas\n"));
		ReleaseMutex(hMutex);//péssima solução usada com I / O
	}
	else
		_tprintf(TEXT("Erro ao criar as threads da bola e teclas\n"));
	if (WaitForSingleObject(hTBola, INFINITE) || (WaitForSingleObject(hTeclas, INFINITE)) == NULL)
		return -1;
	return 0;
}

DWORD WINAPI threadBola(LPVOID param) {
	//int x, y;
	//// posição inicial da bola
	//x = COLUNAS / 2, y = LINHAS - 1;
	//int xd = 1, yd = 1;
	WaitForSingleObject(hMutex, INFINITE);//péssima solução usada com I / O
	gotoxy(x, y);
	_tprintf(TEXT("*"));
	ReleaseMutex(hMutex);//péssima solução usada com I / O

	while (1) {
		WaitForSingleObject(hMutex, INFINITE);//péssima solução usada com I / O
    
		// apaga a posição anterior
		gotoxy(x, y);
		_tprintf(TEXT(" "));
		x -= xd;
		y -= yd;
		if (x > COLUNAS - 2 || x < 2) { // limites direita e esquerda
			xd *= -1;
		}
		//if (y > LINHAS || y < 2) { // limites inferior e superior
		if (y < 2) { // limites superior
			yd *= -1;
		}
		gotoxy(x, y);
		_tprintf(TEXT("*"));

		/*if (y > LINHAS) {
			gotoxy(0, LINHAS + 2);
			_tprintf(TEXT("Perdeu o jogo..."));
			exit(1);
		}*/

		if (y >= LINHAS) // limites inferior
			if (x >= xp && x <= xp + 5)
				yd *= -1;
			else {
				gotoxy(0, LINHAS + 2);
				_tprintf(TEXT("Perdeu o jogo...\n"));
				exit(1);
			}

		gotoxy(COLUNAS + 3, 22);
		_tprintf(TEXT("                         "));
		gotoxy(COLUNAS + 3, 22);
		_tprintf(TEXT("Bola (x,y) = (%.2d, %.2d)"), x, y);
		gotoxy(COLUNAS + 3, 23);
		_tprintf(TEXT("                         "));
		gotoxy(COLUNAS + 3, 23);
		_tprintf(TEXT("Bola (xd,yd) = (%d, %d)"), xd, yd);
		ReleaseMutex(hMutex);//péssima solução usada com I / O
		Sleep(50);
	}
}

DWORD WINAPI threadTeclas(LPVOID param) {
	// barreira do jogador, posição inicial da barreira
	/*int xp = 1, yp = LINHAS, xpa = xp;*/
	WaitForSingleObject(hMutex, INFINITE);//péssima solução usada com I / O
	gotoxy(xp, yp);
	_tprintf(TEXT("_____"));
	ReleaseMutex(hMutex);//péssima solução usada com I / O
	// teclas
	TCHAR key_input;
	while (1) {
		key_input = _gettch();
		key_input = toupper(key_input);
		//_flushall();
		fflush(stdin);
		switch (key_input) {
		case 77: //direta
			if (xp < COLUNAS - 5) {
				WaitForSingleObject(hMutex, INFINITE);//péssima solução usada com I/O
				xpa = xp;
				xp += 5;
				gotoxy(xpa, yp);
				_tprintf(TEXT("     "));
				gotoxy(xp, yp);
				_tprintf(TEXT("_____"));
				//gotoxy(COLUNAS + 3, 24);
				//_tprintf(TEXT("                         "));
				gotoxy(COLUNAS + 3, 24);
				_tprintf(TEXT("Barreira = xp: %.2d, xpa: %.2d"), xp, xpa);
				ReleaseMutex(hMutex);//péssima solução usada com I/O
			}
			break;
		case 75: // esquerda
			if (xp > 1) {
				WaitForSingleObject(hMutex, INFINITE); //péssima solução usada com I/O
				xpa = xp;
				xp -= 5;
				gotoxy(xpa, yp);
				_tprintf(TEXT("     "));
				gotoxy(xp, yp);
				_tprintf(TEXT("_____"));
				//gotoxy(COLUNAS + 3, 24);
				//_tprintf(TEXT("                         "));
				gotoxy(COLUNAS + 3, 24);
				_tprintf(TEXT("Barreira = xp: %.2d, xpa: %.2d"), xp, xpa);
				ReleaseMutex(hMutex);//péssima solução usada com I/O
			}
			break;
		case 27: // ESC = sair
			gotoxy(0, LINHAS + 2);
			exit(1);
			break;
		}
	}
}