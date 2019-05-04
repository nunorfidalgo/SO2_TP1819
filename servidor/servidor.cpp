#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"

#define SHM_MENSAGENS TEXT("SHM_Mensagens")
#define MUTEX_MENSAGENS TEXT("MutexMensagens")
#define EVENTO_MENSAGENS TEXT("EventoMensagens")
HANDLE hMuMensagens;
HANDLE hEvMensagens;
HANDLE hMemMensagens;
MENSAGEM *mensagem;

int inicio_jogo = 0;

// posi��o inicial da bola
int x = COLUNAS / 2, y = LINHAS - 1;
int xd = 1, yd = 1,xa=xd, ya=yd;
int xp = 1, yp = LINHAS, xpa = xp;


#define SHM_JOGO TEXT("SHM_Jogo")
#define MUTEX_JOGO TEXT("MutexJogo")
#define EVENTO_JOGO TEXT("EventoJogo")
HANDLE hMuJogo;
HANDLE hEvJogo;
HANDLE hMemJogo;
JOGO *jogo;

HANDLE hTMensagens, hTJogo, hTBola;

TCHAR nome[NOME];

DWORD WINAPI recebeMensagens(LPVOID param);
DWORD WINAPI enviaJogo(LPVOID param);
DWORD WINAPI threadBola(LPVOID param);

int _tmain(int argc, LPTSTR argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	system("cls");
	_tprintf(TEXT("%s iniciou...\n"), SERVIDOR);


	hMuMensagens = CreateMutex(NULL, FALSE, MUTEX_MENSAGENS);
	hEvMensagens = CreateEvent(NULL, TRUE, FALSE, EVENTO_MENSAGENS);
	hMemMensagens = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(MENSAGEM), SHM_MENSAGENS);
	if (hMuMensagens == NULL || hEvMensagens == NULL || hMemMensagens == NULL) {
		_tprintf(TEXT("[Erro]Cria��o de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	mensagem = (MENSAGEM*)MapViewOfFile(hMemMensagens, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MENSAGEM));
	if (mensagem == NULL) {
		_tprintf(TEXT("[Erro]Mapeamento da mem�ria partilhada(%d)\n"), GetLastError());
		return -1;
	}



	hMuJogo = CreateMutex(NULL, FALSE, MUTEX_JOGO);
	hEvJogo = CreateEvent(NULL, TRUE, FALSE, EVENTO_JOGO);

	hMemJogo = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(JOGO), SHM_JOGO);
	if (hMuJogo == NULL || hEvJogo == NULL || hMemJogo == NULL) {
		_tprintf(TEXT("[Erro] Cria��o de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	jogo = (JOGO*)MapViewOfFile(hMemJogo, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(JOGO));
	if (jogo == NULL) {
		_tprintf(TEXT("[Erro] Mapeamento da mem�ria partilhada (%d)\n"), GetLastError());
		return -1;
	}

	hTMensagens = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)recebeMensagens, NULL, 0, NULL);
	hTJogo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enviaJogo, NULL, 0, NULL);

	//hTBola = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadBola, NULL, 0, NULL);

	if (hTMensagens == NULL && hTJogo == NULL)
		_tprintf(TEXT("Erro ao criar as threads da de recebeMensagens e enviaJogo\n"));

	if (WaitForSingleObject(hTMensagens, INFINITE) || (WaitForSingleObject(hTJogo, INFINITE)) == NULL)
		return -1;

	
	
	//if (hTBola == NULL) {
	//	_tprintf(TEXT("Erro ao criar as threads da bola e teclas\n"));
	//}
	if (WaitForSingleObject(hTBola, INFINITE) == NULL)
	return -1;

	//CloseHandle(hMutex);
	CloseHandle(hTBola);
	


	UnmapViewOfFile(mensagem);
	UnmapViewOfFile(jogo);
	CloseHandle(hMuMensagens);
	CloseHandle(hMuJogo);
	CloseHandle(hEvMensagens);
	CloseHandle(hEvJogo);
	CloseHandle(hMemMensagens);
	CloseHandle(hMemJogo);

	return 0;
}

DWORD WINAPI recebeMensagens(LPVOID param) {
	while (1)
	{
		//_tprintf(TEXT("Aguardo mensagem...\n"));

		WaitForSingleObject(hEvMensagens, INFINITE);
		WaitForSingleObject(hMuMensagens, INFINITE);

		xp = mensagem->jogadorx;
		yp = mensagem->jogadory;

		//_tprintf(TEXT("Recebi Mensagem: '%s'=(%d,%d) | Bola=(%d,%d)\n"), mensagem->nome, mensagem->jogadorx, mensagem->jogadory, mensagem->bolax, mensagem->bolay);
		_tprintf(TEXT("Jogador '%s' vai iniciar o jogo\n"), mensagem->nome);
		/*if (!_tcscmp (mensagem->nome, TEXT("")))
			inicio_jogo = 1;*/
		if (mensagem->inicioJogo == 1) {
			hTBola = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadBola, NULL, 0, NULL);
			if (hTBola == NULL) {
				_tprintf(TEXT("Erro ao criar as threads da bola e teclas\n"));
			}
			else {
				mensagem->inicioJogo = 0;
				//_tcscpy_s(mensagem->nome, TEXT(""));
				//mensagem->nome = NULL;
				_tprintf(TEXT("Lancei Thread vai iniciar o jogo\n"));
				_tcscpy_s(jogo->jogador.nome, mensagem->nome);
				_tprintf(TEXT("Nome do jogador: %s\n"),jogo->jogador.nome);
				//_tcscpy_s(jogo->jogador.nome, mensagem->nome);
				//_stprintf_s(mensagem->nome, TEXTO, TEXT("Jogador confirmado."));
			}

		}
		ReleaseMutex(hMuMensagens); 
		//Sleep(500);
	}		
}

DWORD WINAPI enviaJogo(LPVOID param) {
	//int i = 1;
	while (1)
	{
		WaitForSingleObject(hMuJogo, INFINITE);

	//	_stprintf_s(nome, sizeof(nome), TEXT("Teste do jogo %d"), i);
		//_tcscpy_s(jogo->nome, sizeof(nome), nome);
		jogo->bola.coordAnt.x = xa;
		jogo->bola.coordAnt.y = ya;

		jogo->bola.coord.x = x;
		jogo->bola.coord.y = y;

		jogo->jogador.barreira.coordAnt.x = xpa;
		jogo->jogador.barreira.coordAnt.y = yp;

		jogo->jogador.barreira.coord.x = xp;
		jogo->jogador.barreira.coord.y = yp;
		//i++;
		//_tprintf(TEXT("Bola = %d , %d\n"), jogo->bola.coord.x, jogo->bola.coord.y);
		//_tprintf(TEXT("Jogador = %d , %d\n"), jogo->jogador.barreira.coord.x, jogo->jogador.barreira.coord.y);
		//_tprintf(TEXT("Envio Jogo: '%s'\n"), jogo->nome);

		SetEvent(hEvJogo);
		ReleaseMutex(hMuJogo);
		ResetEvent(hEvJogo);

		//Sleep(500);
	}
}


DWORD WINAPI threadBola(LPVOID param) {
	//int x, y;
	//// posi��o inicial da bola
	//x = COLUNAS / 2, y = LINHAS - 1;
	//int xd = 1, yd = 1;

	//_tprintf(TEXT("While\n"));
	while (1) {

		WaitForSingleObject(hMuJogo , INFINITE);//p�ssima solu��o usada com I / O

		// apaga a posi��o anterior
		//gotoxy(x, y);
		//_tprintf(TEXT(" "));
		xa = x;
		ya = y;
		x -= xd;
		y -= yd;
		//_tprintf(TEXT("Bola = %d , %d\n"), x,y);
		if (x > COLUNAS - 2 || x < 2) { // limites direita e esquerda
			xd *= -1;
		}
		if (y >= LINHAS || y < 2) { // limites inferior e superior
		//if (y < 2) { // limites superior
			yd *= -1;
		}
		//gotoxy(x, y);
		//_tprintf(TEXT("*"));

		/*if (y > LINHAS) {
			gotoxy(0, LINHAS + 2);
			_tprintf(TEXT("Perdeu o jogo..."));
			exit(1);
		}*/

		//if (y >= LINHAS) // limites inferior
		//	if (x >= xp && x <= xp + 5)
		//		yd *= -1;
		//	else {
		//		gotoxy(0, LINHAS + 2);
		//		_tprintf(TEXT("Perdeu o jogo...\n"));
		//		exit(1);
		//	}

		//gotoxy(COLUNAS + 3, 22);
		//_tprintf(TEXT("                         "));
		//gotoxy(COLUNAS + 3, 22);
		//_tprintf(TEXT("Bola (x,y) = (%.2d, %.2d)"), x, y);
		//gotoxy(COLUNAS + 3, 23);
		//_tprintf(TEXT("                         "));
		//gotoxy(COLUNAS + 3, 23);
		//_tprintf(TEXT("Bola (xd,yd) = (%d, %d)"), xd, yd);
		ReleaseMutex(hMuJogo);//p�ssima solu��o usada com I / O
		Sleep(100);
	}
}