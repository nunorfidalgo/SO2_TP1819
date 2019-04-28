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

HANDLE hMutex;
// posição inicial da bola
int x = COLUNAS / 2, y = LINHAS - 1;
int xd = 1, yd = 1;
int xp = 1, yp = LINHAS, xpa = xp;

DWORD WINAPI threadBola(LPVOID param);
DWORD WINAPI threadTeclas(LPVOID param);

TCHAR NomeMemoria[] = TEXT("teste");
HANDLE hEvento;
HANDLE hMemoria;

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	/*HANDLE hTBola, hTeclas;
	HANDLE PacoteCli, hMapMemCli;

	system("cls");
	_tprintf(TEXT("%s iniciou...\n"), CLIENTE);
	PacoteCli = AcedeMemPartCom(hMapMemCli);*/



	Pacote *pacote;
	//char init = 1;


	system("cls");
	// criar mutex
	hMutex = CreateMutex(NULL, FALSE, TEXT("Mutex"));
	// Criar MUTEX
	// mutex
	//hMutex = CreateMutex(NULL, TRUE, TEXT("MutexIn"));
	//if (MutexIn == NULL) {
	//	_tprintf(TEXT("CreateMutex error: %d\n"), GetLastError());
	//	return 1;
	//}

	hEvento = CreateEvent(NULL, TRUE, FALSE, TEXT("Evento"));

	/*hMemoria = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(Pacote), NomeMemoria);*/
	hMemoria = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, NomeMemoria);
	if (hMutex == NULL || hEvento == NULL || hMemoria == NULL) {
		_tprintf(TEXT("[Erro] Criação de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	// verificar se ja existe shm
	/*if (GetLastError() == ERROR_ALREADY_EXISTS) {
		init = 0;
	}*/

	pacote = (Pacote*)MapViewOfFile(hMemoria, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Pacote));
	if (pacote == NULL) {
		_tprintf(TEXT("[Erro]Mapeamento da memória partilhada(%d)\n"), GetLastError());
		return -1;
	}

	// verificar se ja existe shm
	//if (GetLastError() != ERROR_ALREADY_EXISTS) {
	//	// colocar IN a zero...
	//	_tcscpy_s(shm->nome, sizeof(TCHAR), TEXT(""));
	//	shm->bolax = 0;
	//	shm->bolax = 0;
	//	shm->jogadorx = 0;
	//	shm->jogadory = 0;
	//	// (Mutex ou) restaurar valor do semaforo PodeEscrever(+10)... ou seja release de 10 unidades, alterar na criacao para 0 ate 10
	//	/*ReleaseSemaphore(PodeEscrever, 10, NULL);*/
	//	ReleaseMutex(hMutex);
	//}

	/*for (int i = 1; i <= 5; i++)*/
	int i = 1;
	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);

		//_stprintf_s(shm->nome, sizeof(TCHAR) * 26, TEXT("Jogador %d [Thread Id: %d]"), i, GetCurrentProcessId());
		//_tcscpy_s(shm->nome, sizeof(TCHAR) * 7, TEXT("Jogador"));
		pacote->bolax = i;
		pacote->bolay = i;
		pacote->jogadorx = i;
		pacote->jogadory = i;
		i++;

		SetEvent(hEvento);
		ReleaseMutex(hMutex);
		ResetEvent(hEvento);
		Sleep(1000);
	}

	UnmapViewOfFile(pacote);

	CloseHandle(hMutex);
	CloseHandle(hEvento);
	CloseHandle(hMemoria);

	//hMutex = CreateMutex(NULL, FALSE, NULL);
	//if (hMutex == NULL) {
	//	_tprintf(TEXT("Erro ao criar mutex: %d\n"), GetLastError());
	//	return 1;
	//}

	//// Limites do jogo
	//for (x = 0; x < COLUNAS; x++) {
	//	gotoxy(x, 0);
	//	_tprintf(TEXT("-"));
	//	gotoxy(x, LINHAS + 1);
	//	_tprintf(TEXT("-"));
	//}

	//for (y = 0; y <= LINHAS + 1; y++) {
	//	gotoxy(0, y);
	//	_tprintf(TEXT("|"));
	//	gotoxy(COLUNAS, y);
	//	_tprintf(TEXT("|"));
	//}

	//// Tijolos
	///*for (y = 4; y < 7; y++)
	//	for (x = 6; x < COLUNAS - 6; x++) {
	//		gotoxy(x, y);
	//		_tprintf(TEXT("#"));
	//	}

	//for (y = 8; y < 11; y++)
	//	for (x = 6; x < COLUNAS - 6; x++) {
	//		gotoxy(x, y);
	//		_tprintf(TEXT("&"));
	//	}*/


	//gotoxy(COLUNAS + 3, 0);
	//_tprintf(TEXT("-------------- ARKNOID / BREAKOUT------------\n"));
	//gotoxy(COLUNAS + 3, 2);
	//gotoxy(COLUNAS + 3, 26);
	//_tprintf(TEXT("ESC - sair"));

	//hTBola = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadBola, NULL, 0, NULL);
	//hTeclas = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTeclas, NULL, 0, NULL);

	//if (hTBola != NULL && hTeclas != NULL) {
	//	WaitForSingleObject(hMutex, INFINITE); //péssima solução usada com I / O
	//	gotoxy(COLUNAS + 3, 3);
	//	_tprintf(TEXT("Lancei as threads da bola e das teclas\n"));
	//	ReleaseMutex(hMutex);//péssima solução usada com I / O
	//}
	//else
	//	_tprintf(TEXT("Erro ao criar as threads da bola e teclas\n"));
	//if (WaitForSingleObject(hTBola, INFINITE) || (WaitForSingleObject(hTeclas, INFINITE)) == NULL)
	//	return -1;

	//CloseHandle(hMutex);
	//CloseHandle(hTBola);
	//CloseHandle(hTeclas);

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