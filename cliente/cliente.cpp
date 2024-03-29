#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "../bridge/bridge.h"



DWORD WINAPI threadBola(LPVOID param);
DWORD WINAPI threadTeclas(LPVOID param);

void inicioJogo();
void imprimeTabuleiro();
// barreira do jogador, posição inicial da barreira
int xp = 1, yp = LINHAS; //xpa = xp;

TCHAR nome[NOME];

#define SHM_MENSAGENS TEXT("SHM_Mensagens")
#define MUTEX_MENSAGENS TEXT("MutexMensagens")
#define EVENTO_MENSAGENS TEXT("EventoMensagens")
HANDLE hMuMensagens;
HANDLE hEvMensagens;
HANDLE hMemMensagens;
MENSAGEM *mensagem;

#define SHM_JOGO TEXT("SHM_Jogo")
#define MUTEX_JOGO TEXT("MutexJogo")
#define EVENTO_JOGO TEXT("EventoJogo")
HANDLE hMuJogo;
HANDLE hEvJogo;
HANDLE hMemJogo;


JOGO *jogo;

HANDLE hTMensagens, hTJogo,hTeclas;

DWORD WINAPI envioMensagem(LPVOID param);
DWORD WINAPI recebeJogo(LPVOID param);

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	system("cls");
	//_tprintf(TEXT("%s iniciou...\n"), CLIENTE);
	
	
	hMuMensagens = CreateMutex(NULL, FALSE, MUTEX_MENSAGENS);
	hEvMensagens = CreateEvent(NULL, TRUE, FALSE, EVENTO_MENSAGENS);

	
	hMemMensagens = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, SHM_MENSAGENS);
	if (hMuMensagens == NULL || hEvMensagens == NULL || hMemMensagens == NULL) {
		_tprintf(TEXT("[Erro] Criação de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	mensagem = (MENSAGEM*)MapViewOfFile(hMemMensagens, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MENSAGEM));
	if (mensagem == NULL) {
		_tprintf(TEXT("[Erro: %s] Mapeamento da memória partilhada1 (%d)\n"), SHM_MENSAGENS, GetLastError());
		return -1;
	}


	hMuJogo = CreateMutex(NULL, FALSE, MUTEX_JOGO);
	hEvJogo = CreateEvent(NULL, TRUE, FALSE, EVENTO_JOGO);

	hMemJogo = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, SHM_JOGO);
	if (hMuJogo == NULL || hEvJogo == NULL || hMemJogo == NULL) {
		_tprintf(TEXT("[Erro] Criação de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	jogo = (JOGO*)MapViewOfFile(hMemJogo, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(JOGO));
	if (jogo == NULL) {
		_tprintf(TEXT("[Erro: %s] Mapeamento da memória partilhada 2(%d)\n"), SHM_JOGO, GetLastError());
		return -1;
	}
	inicioJogo();
	system("cls");
	imprimeTabuleiro();

	hTMensagens = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)envioMensagem, NULL, 0, NULL);
	hTJogo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)recebeJogo, NULL, 0, NULL);
	hTeclas = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTeclas, NULL, 0, NULL);

	if (hTMensagens == NULL || hTJogo == NULL) {
		_tprintf(TEXT("Erro ao criar as threads da bola e teclas\n"));
		return -1;
	}

	if (WaitForSingleObject(hTMensagens, INFINITE) || (WaitForSingleObject(hTJogo, INFINITE)) == NULL)
		return -1;
	
	if (hTeclas == NULL) {

		_tprintf(TEXT("Erro ao criar as threads da bola e teclas\n"));
	}
	if ((WaitForSingleObject(hTeclas, INFINITE)) == NULL)
		return -1;

	UnmapViewOfFile(mensagem);
	UnmapViewOfFile(jogo);
	CloseHandle(hMuMensagens);
	CloseHandle(hMuJogo);
	CloseHandle(hEvMensagens);
	CloseHandle(hEvJogo);
	CloseHandle(hMemMensagens);
	CloseHandle(hMemJogo);
	CloseHandle(hTeclas);

	return 0;
}

void inicioJogo() {
	TCHAR nome[TEXTO];
	_tprintf(TEXT("Introduza o nome\n"));
	_getts_s(nome);
	_tprintf_s(TEXT("Jogador: %s"), nome);

	_tcscpy_s(mensagem->nome,sizeof(nome),nome);
	mensagem->inicioJogo = 1;
}

void imprimeTabuleiro() {

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
}



DWORD WINAPI threadTeclas(LPVOID param) {
	
	TCHAR key_input;
	while (1) {
		key_input = _gettch();
		key_input = toupper(key_input);
		fflush(stdin);
		switch (key_input) {
		case 77: //direita
			if (xp < COLUNAS - 5) {
				xp += 5;
			}
			break;
		case 75: // esquerda
			if (xp > 1) {
				xp -= 5;
			}
			break;
		case 27: // ESC = sair
			//gotoxy(0, LINHAS + 2);
			exit(1);
			break;
		}
	}
}

DWORD WINAPI envioMensagem(LPVOID param) {
	//int i = 1;
	while (1)
	{
		WaitForSingleObject(hMuMensagens, INFINITE);

		mensagem->bolax = -1;
		mensagem->bolay = -1;
		mensagem->jogadorx = xp;
		mensagem->jogadory = yp;
						
		SetEvent(hEvMensagens);
		ReleaseMutex(hMuMensagens);
		ResetEvent(hEvMensagens);

		Sleep(500);
	}
}

DWORD WINAPI recebeJogo(LPVOID param) {
	
	while (1){
	
		WaitForSingleObject(hEvJogo, INFINITE);
		WaitForSingleObject(hMuJogo, INFINITE);

		gotoxy(jogo->bola.coordAnt.x, jogo->bola.coordAnt.y);
		_tprintf(TEXT(" "));
		gotoxy(jogo->bola.coord.x, jogo->bola.coord.y);
		_tprintf(TEXT("*"));

		gotoxy(jogo->jogador.barreira.coordAnt.x, jogo->jogador.barreira.coordAnt.y);
	/*	for (int x = 1; x < COLUNAS; x++) {
			gotoxy(x, LINHAS);
			_tprintf(TEXT(" "));
		}*/
		_tprintf(TEXT("                                        "));
		gotoxy(jogo->jogador.barreira.coord.x, jogo->jogador.barreira.coord.y);
		_tprintf(TEXT("_____"));

		gotoxy(COLUNAS + 3, 24);
		_tprintf(TEXT("Jogador: %s"), jogo->jogador.nome);

		ReleaseMutex(hMuJogo);
		//Sleep(150);
	}
}