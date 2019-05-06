﻿#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"

#define TAM 200

BOLA bola;
SincControl sincControl;

HANDLE hServidor, hLogin;
HANDLE hTMensagens, hTJogo, hTBola;
DWORD hTMensagensId, hTJogoId, hTBolaId;

bool verificaInstancia();
DWORD WINAPI recebeMensagens(LPVOID param);
DWORD WINAPI enviaJogo(LPVOID param);
DWORD WINAPI threadBola(LPVOID param);

int escreveRegisto();
int leRegisto();

int _tmain(int argc, LPTSTR argv[])
{

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("%s: Pronto...\n"), SERVIDOR);

	if (escreveRegisto() == -1) {
		_tprintf(TEXT("%s: [Erro: %d] Não foi possível salvar os pontos no registo!\n"), SERVIDOR, GetLastError());
	}
	else {
		if (leRegisto() == -1) {
			_tprintf(TEXT("%s: [Erro: %d] Sem pontos no registo!\n"), SERVIDOR, GetLastError());
		}
	}

	if (verificaInstancia())
		return -1;

	if (!AcessoMensagensServidor(sincControl))
		return -1;

	if (!AcessoJogoServidor(sincControl))
		return -1;

	_tprintf(TEXT("%s: Espera nome jogador...\n"), SERVIDOR);
	hLogin = CreateEvent(NULL, TRUE, FALSE, TEXT("LOGIN"));
	if (hLogin == NULL) {
		_tprintf(TEXT("%s: [ERRO] Criação evento do login (%d)\n"), SERVIDOR, GetLastError());
		return -1;
	}
	WaitForSingleObject(hLogin, INFINITE);
	_tprintf(TEXT("%s: O jogo começou...\n"), SERVIDOR);
	CloseHandle(hLogin);

	hTMensagens = CreateThread(NULL, 0, recebeMensagens, NULL, 0, &hTMensagensId);
	if (hTMensagens == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das mensagens...\n"), SERVIDOR, GetLastError(), hTMensagensId);
		return -1;
	}

	hTJogo = CreateThread(NULL, 0, enviaJogo, NULL, 0, &hTJogoId);
	if (hTJogo == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] do jogo...\n"), SERVIDOR, GetLastError(), hTJogoId);
		return -1;
	}

	hTBola = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadBola, NULL, 0, &hTBolaId);
	if (hTBola == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao criar a thread[%d] da bola...\n"), SERVIDOR, GetLastError(), hTBolaId);
		return -1;
	}

	if (WaitForSingleObject(hTMensagens, INFINITE) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das mensagens...\n"), SERVIDOR, GetLastError(), hTMensagensId);
	}
	if ((WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] do jogo...\n"), SERVIDOR, GetLastError(), hTJogoId);
	}
	if ((WaitForSingleObject(hTBola, INFINITE)) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] da bola...\n"), SERVIDOR, GetLastError(), hTBolaId);
	}

	_tprintf(TEXT("%s: [LastError %d] terminou...\n"), SERVIDOR, GetLastError());

	closeSincControl(sincControl);
	CloseHandle(hTMensagens);
	CloseHandle(hTJogo);
	CloseHandle(hTBola);
	CloseHandle(hServidor);
	return 0;
}

bool verificaInstancia() {
	hServidor = CreateEventW(NULL, TRUE, FALSE, SERVIDOR);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hServidor);
		hServidor = NULL;
		_tprintf(TEXT("%s: [Erro: %d]Já exite uma instância do servidor a correr\n"), SERVIDOR, GetLastError());
		return true;
	}
	return false;
}

DWORD WINAPI recebeMensagens(LPVOID param) {
	int m = 1;
	while (!sincControl.mensagem->termina) {

		WaitForSingleObject(sincControl.hEventoMensagem, INFINITE);
		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		_tprintf(TEXT("[Thread: %d] Recebi Mensagem [%d]: Jogador: '%s'=(%d,%d) | termina: %d\n"), GetCurrentThreadId(), m, sincControl.mensagem->jogador.nome, sincControl.mensagem->jogador.barreira.coord.x, sincControl.mensagem->jogador.barreira.coord.y, sincControl.mensagem->termina);

		_tcscpy_s(sincControl.jogo->jogador.nome, sincControl.mensagem->jogador.nome);
		sincControl.jogo->jogador.barreira.coord.x = sincControl.mensagem->jogador.barreira.coord.x;
		sincControl.jogo->jogador.barreira.coord.y = sincControl.mensagem->jogador.barreira.coord.y;
		sincControl.jogo->termina = sincControl.mensagem->termina;
		m++;

		ReleaseMutex(sincControl.hMutexMensagem);

	}
	return 0;
}

DWORD WINAPI enviaJogo(LPVOID param) {
	int j = 1;
	while (!sincControl.jogo->termina) {

		SetEvent(sincControl.hEventoJogo);
		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

		sincControl.jogo->bola.coordAnt.x = bola.coordAnt.x;
		sincControl.jogo->bola.coordAnt.y = bola.coordAnt.y;
		sincControl.jogo->bola.coord.x = bola.coord.x;
		sincControl.jogo->bola.coord.y = bola.coord.y;

		_tprintf(TEXT("[Thread: %d] Envio Jogo [%d] Jogador: '%s' (x,y)=(%d, %d) | Bola (x,y)=(%d, %d) | termina: %d\n"), GetCurrentThreadId(), j, sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, sincControl.jogo->termina);
		j++;

		Sleep(VEL_JOGO);

		ReleaseMutex(sincControl.hMutexJogo);
		ResetEvent(sincControl.hEventoJogo);

	}
	return 0;
}

DWORD WINAPI threadBola(LPVOID param) {

	bola.coord.x = COLUNAS / 2;
	bola.coord.y = LINHAS - 1;
	bola.coordAnt.x = bola.coord.x;
	bola.coordAnt.y = bola.coord.y;
	bola.direcao.x = 1;
	bola.direcao.y = 1;

	while (!sincControl.jogo->termina) {
		//while (true) { //!sincControl.jogo->termina
		//WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

		bola.coordAnt.x = bola.coord.x;
		bola.coordAnt.y = bola.coord.y;
		bola.coord.x -= bola.direcao.x;
		bola.coord.y -= bola.direcao.y;

		if (bola.coord.x > COLUNAS - 2 || bola.coord.x < 2) { // limites direita e esquerda
			bola.direcao.x *= -1;
		}
		if (bola.coord.y > LINHAS || bola.coord.y < 2) { // limites inferior e superior
		//if (y < 2) { // limites superior
			bola.direcao.y *= -1;
		}

		/*if (y > LINHAS) {
			gotoxy(0, LINHAS + 2);
			_tprintf(TEXT("Perdeu o jogo..."));
			exit(1);
		}*/

		// barreira
		//if (y >= LINHAS) // limites inferior
		//	if (x >= xp && x <= xp + 5)
		//		yd *= -1;
		//	else {
		//		gotoxy(0, LINHAS + 2);
		//		_tprintf(TEXT("Perdeu o jogo...\n"));
		//		exit(1);
		//	}
		//ReleaseMutex(sincControl.hMutexJogo);
		Sleep(VEL_JOGO);
	}
	return 0;
}

int escreveRegisto() {

	//TCHAR frase[TAM];
	HKEY chave;
	DWORD queAconteceu;
	//TCHAR str[TAM], autores[TAM], top_ten[TAM], meta[TAM], pontuacoes[TAM];

	//Criar/abrir uma chave em HKEY_CURRENT_USER\Software\TP_SO2_2018_2019
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\TP_SO2_2018_2019"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &chave, &queAconteceu) != ERROR_SUCCESS) {
		_tprintf(TEXT("Erro ao criar/abrir chave (%d)\n"), GetLastError());
		return -1;
	}
	else {
		//Se a chave foi criada, inicializar os valores
		if (queAconteceu == REG_CREATED_NEW_KEY) {
			_tprintf(TEXT("Chave: HKEY_CURRENT_USER\\Software\\TP_SO2_2018_2019 criada\n"));
			//Criar valor "Autor" = "Nuno Fidalgo e Cláudio Melo"
			RegSetValueEx(chave, TEXT("Autores"), 0, REG_SZ, (LPBYTE)TEXT("Nuno Fidalgo e Cláudio Melo"), _tcslen(TEXT("Nuno Fidalgo e Cláudio Melo")) * sizeof(TCHAR));

			RegSetValueEx(chave, TEXT("Meta"), 0, REG_SZ, (LPBYTE)TEXT("Meta 1"), _tcslen(TEXT("Meta 1")) * sizeof(TCHAR));

			RegSetValueEx(chave, TEXT("Top Ten"), 0, REG_SZ, (LPBYTE)TEXT("Nuno,Cláudio,Cláudio,Nuno,Melo,Fidalgo,21170023,21140369"), _tcslen(TEXT("Nuno,Cláudio,Cláudio,Nuno,Melo,Fidalgo,21170023,21140369")) * sizeof(TCHAR));
			RegSetValueEx(chave, TEXT("Pontuações"), 0, REG_SZ, (LPBYTE)TEXT("2931,292,198,156,145,133,132,15"), _tcslen(TEXT("2931,292,198,156,145,133,132,15")) * sizeof(TCHAR));
		}
	}
	return 0;
}

int leRegisto() {

	HKEY chave;
	DWORD queAconteceu, tamanho;
	TCHAR str[TAM], top_ten[TAM], pontuacoes[TAM];

	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\TP_SO2_2018_2019"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &chave, &queAconteceu) != ERROR_SUCCESS) {
		_tprintf(TEXT("Erro ao criar/abrir chave (%d)\n"), GetLastError());
		return -1;
	}
	else {
		//Se a chave foi aberta, ler os valores lá guardados
		if (queAconteceu == REG_OPENED_EXISTING_KEY) {
			tamanho = 200;
			RegQueryValueEx(chave, TEXT("Top Ten"), NULL, NULL, (LPBYTE)top_ten, &tamanho);
			top_ten[tamanho / sizeof(TCHAR)] = '\0';

			tamanho = 200;
			RegQueryValueEx(chave, TEXT("Pontuações"), NULL, NULL, (LPBYTE)pontuacoes, &tamanho);
			pontuacoes[tamanho / sizeof(TCHAR)] = '\0';

			_stprintf_s(str, TAM, TEXT("Top Ten: %s\nPontuação: %s\n"), top_ten, pontuacoes);
			_tprintf(TEXT("Lido do Registry:\n%s"), str);
		}
		else {
			_tprintf(TEXT("Erro ao criar/abrir chave (%d)\n"), GetLastError());
			return -1;
		}
		RegCloseKey(chave);
		return 0;
	}
}

