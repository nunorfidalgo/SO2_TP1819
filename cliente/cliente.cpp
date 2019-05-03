#define _CRT_SECURE_NO_WARNINGS
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

// tamanho padrão da linha de comandos do windows
#define COLUNAS 41 // x
#define LINHAS 26 // y

//HANDLE hMutex;
// posição inicial da bola
//int x = COLUNAS / 2, y = LINHAS - 1;
//int xd = 1, yd = 1;
//int xp = 1, yp = LINHAS, xpa = xp;
//
//DWORD WINAPI threadBola(LPVOID param);
//DWORD WINAPI threadTeclas(LPVOID param);

TCHAR nome[TEXTO];
SincControl sincControl;

HANDLE hTMensagens, hTJogo;

DWORD WINAPI envioMensagem(LPVOID param);
DWORD WINAPI recebeJogo(LPVOID param);

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("%s iniciou...\n"), CLIENTE);

	//sincControl.hMutexMensagem = CreateMutex(NULL, FALSE, MUTEX_MENSAGEM);
	//sincControl.hEventoMensagem = CreateEvent(NULL, TRUE, FALSE, EVENTO_MENSAGEM);
	sincControl.hMutexMensagem = OpenMutex(SYNCHRONIZE, FALSE, MUTEX_MENSAGEM);
	sincControl.hEventoMensagem = OpenEvent(FILE_MAP_WRITE, FALSE, EVENTO_MENSAGEM);
	sincControl.hMemMensagem = OpenFileMapping(FILE_MAP_WRITE, TRUE, SHM_MENSAGEM);
	if (sincControl.hMutexMensagem == NULL || sincControl.hEventoMensagem == NULL || sincControl.hMemMensagem == NULL) {
		_tprintf(TEXT("[Erro: %s] Criação de objectos (%d)\n"), MENSAGEM_TXT, GetLastError());
		return -1;
	}
	sincControl.mensagem = (MENSAGEM*)MapViewOfFile(sincControl.hMemMensagem, FILE_MAP_WRITE, 0, 0, sizeof(MENSAGEM));
	if (sincControl.mensagem == NULL) {
		_tprintf(TEXT("[Erro: %s] Mapeamento da memória partilhada (%d)\n"), MENSAGEM_TXT, GetLastError());
		return -1;
	}

	sincControl.hMutexJogo = OpenMutex(SYNCHRONIZE, FALSE, MUTEX_JOGO);
	sincControl.hEventoJogo = OpenEvent(FILE_MAP_WRITE, FALSE, EVENTO_JOGO);
	sincControl.hMemJogo = OpenFileMapping(FILE_MAP_READ, TRUE, SHM_JOGO);
	if (sincControl.hMutexJogo == NULL || sincControl.hEventoJogo == NULL || sincControl.hMemJogo == NULL) {
		_tprintf(TEXT("[Erro: %s] Criação de objectos (%d)\n"), JOGO_TXT, GetLastError());
		return -1;
	}
	sincControl.jogo = (JOGO*)MapViewOfFile(sincControl.hMemJogo, FILE_MAP_READ, 0, 0, sizeof(JOGO));
	if (sincControl.jogo == NULL) {
		_tprintf(TEXT("[Erro: %s] Mapeamento da memória partilhada (%d)\n"), JOGO_TXT, GetLastError());
		return -1;
	}

	hTMensagens = CreateThread(NULL, 0, envioMensagem, NULL, 0, NULL);
	hTJogo = CreateThread(NULL, 0, recebeJogo, NULL, 0, NULL);

	if (hTMensagens == NULL || hTJogo == NULL) {
		_tprintf(TEXT("%s Erro ao criar as threads da de recebeMensagens e enviaJogo\n"), CLIENTE);
		return -1;
	}

	if (WaitForSingleObject(hTMensagens, INFINITE) || (WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		_tprintf(TEXT("%s wait stop\n"), CLIENTE);
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

DWORD WINAPI envioMensagem(LPVOID param) {
	_tprintf(TEXT("%s envioMensagem\n"), CLIENTE);
	int i = 1;
	MENSAGEM msg;
	while (1)
	{
		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		_stprintf_s(nome, TEXTO, TEXT("Jogador %d"), i);
		_tcscpy_s(msg.nome, nome);
		msg.bolax = i;
		msg.bolay = i;
		msg.jogadorx = i;
		msg.jogadory = i;
		i++;
		//_tprintf(TEXT("Envio Mensagem: '%s'=(%d,%d) | Bola=(%d,%d)\n"), msg.nome, msg.jogadorx, msg.jogadory, msg.bolax, msg.bolay);

		CopyMemory(sincControl.mensagem, &msg, sizeof(MENSAGEM));
		//_tcscpy_s(sincControl.mensagem->nome, msg.nome);
		////_tcscpy_s(sincControl.mensagem->nome, sizeof(msg.nome), msg.nome);
		//sincControl.mensagem->bolax = msg.bolax;
		//sincControl.mensagem->bolay = msg.bolay;
		//sincControl.mensagem->jogadorx = msg.jogadorx;
		//sincControl.mensagem->jogadory = msg.jogadory;

		_tprintf(TEXT("Envio Mensagem: '%s' = (%d,%d) | Bola = (%d,%d)\n"), sincControl.mensagem->nome, sincControl.mensagem->jogadorx, sincControl.mensagem->jogadory, sincControl.mensagem->bolax, sincControl.mensagem->bolay);
		//_tprintf(TEXT("Envio Mensagem: '%s'\n"), sincControl.mensagem->nome);

		SetEvent(sincControl.hEventoMensagem);
		ReleaseMutex(sincControl.hMutexMensagem);
		ResetEvent(sincControl.hEventoMensagem);

		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI recebeJogo(LPVOID param) {
	//_tprintf(TEXT("%s recebeJogo\n"), CLIENTE);
	while (1)
	{
		_tprintf(TEXT("Aguardo Jogo: "));

		WaitForSingleObject(sincControl.hEventoJogo, INFINITE);
		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

		_tprintf(TEXT("Recebi Jogo: '%s' = (%d, %d) | Bola = (%d, %d)\n"), sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);

		ReleaseMutex(sincControl.hMutexJogo);
		Sleep(1000);
	}
	return 0;
}








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




//
//DWORD WINAPI threadBola(LPVOID param) {
//	//int x, y;
//	//// posição inicial da bola
//	//x = COLUNAS / 2, y = LINHAS - 1;
//	//int xd = 1, yd = 1;
//	WaitForSingleObject(hMutex, INFINITE);//péssima solução usada com I / O
//	gotoxy(x, y);
//	_tprintf(TEXT("*"));
//	ReleaseMutex(hMutex);//péssima solução usada com I / O
//
//	while (1) {
//		WaitForSingleObject(hMutex, INFINITE);//péssima solução usada com I / O
//
//		// apaga a posição anterior
//		gotoxy(x, y);
//		_tprintf(TEXT(" "));
//		x -= xd;
//		y -= yd;
//		if (x > COLUNAS - 2 || x < 2) { // limites direita e esquerda
//			xd *= -1;
//		}
//		//if (y > LINHAS || y < 2) { // limites inferior e superior
//		if (y < 2) { // limites superior
//			yd *= -1;
//		}
//		gotoxy(x, y);
//		_tprintf(TEXT("*"));
//
//		/*if (y > LINHAS) {
//			gotoxy(0, LINHAS + 2);
//			_tprintf(TEXT("Perdeu o jogo..."));
//			exit(1);
//		}*/
//
//		if (y >= LINHAS) // limites inferior
//			if (x >= xp && x <= xp + 5)
//				yd *= -1;
//			else {
//				gotoxy(0, LINHAS + 2);
//				_tprintf(TEXT("Perdeu o jogo...\n"));
//				exit(1);
//			}
//
//		gotoxy(COLUNAS + 3, 22);
//		_tprintf(TEXT("                         "));
//		gotoxy(COLUNAS + 3, 22);
//		_tprintf(TEXT("Bola (x,y) = (%.2d, %.2d)"), x, y);
//		gotoxy(COLUNAS + 3, 23);
//		_tprintf(TEXT("                         "));
//		gotoxy(COLUNAS + 3, 23);
//		_tprintf(TEXT("Bola (xd,yd) = (%d, %d)"), xd, yd);
//		ReleaseMutex(hMutex);//péssima solução usada com I / O
//		Sleep(50);
//	}
//}
//
//DWORD WINAPI threadTeclas(LPVOID param) {
//	// barreira do jogador, posição inicial da barreira
//	/*int xp = 1, yp = LINHAS, xpa = xp;*/
//	WaitForSingleObject(hMutex, INFINITE);//péssima solução usada com I / O
//	gotoxy(xp, yp);
//	_tprintf(TEXT("_____"));
//	ReleaseMutex(hMutex);//péssima solução usada com I / O
//	// teclas
//	TCHAR key_input;
//	while (1) {
//		key_input = _gettch();
//		key_input = toupper(key_input);
//		//_flushall();
//		fflush(stdin);
//		switch (key_input) {
//		case 77: //direta
//			if (xp < COLUNAS - 5) {
//				WaitForSingleObject(hMutex, INFINITE);//péssima solução usada com I/O
//				xpa = xp;
//				xp += 5;
//				gotoxy(xpa, yp);
//				_tprintf(TEXT("     "));
//				gotoxy(xp, yp);
//				_tprintf(TEXT("_____"));
//				//gotoxy(COLUNAS + 3, 24);
//				//_tprintf(TEXT("                         "));
//				gotoxy(COLUNAS + 3, 24);
//				_tprintf(TEXT("Barreira = xp: %.2d, xpa: %.2d"), xp, xpa);
//				ReleaseMutex(hMutex);//péssima solução usada com I/O
//			}
//			break;
//		case 75: // esquerda
//			if (xp > 1) {
//				WaitForSingleObject(hMutex, INFINITE); //péssima solução usada com I/O
//				xpa = xp;
//				xp -= 5;
//				gotoxy(xpa, yp);
//				_tprintf(TEXT("     "));
//				gotoxy(xp, yp);
//				_tprintf(TEXT("_____"));
//				//gotoxy(COLUNAS + 3, 24);
//				//_tprintf(TEXT("                         "));
//				gotoxy(COLUNAS + 3, 24);
//				_tprintf(TEXT("Barreira = xp: %.2d, xpa: %.2d"), xp, xpa);
//				ReleaseMutex(hMutex);//péssima solução usada com I/O
//			}
//			break;
//		case 27: // ESC = sair
//			gotoxy(0, LINHAS + 2);
//			exit(1);
//			break;
//		}
//	}
//}

