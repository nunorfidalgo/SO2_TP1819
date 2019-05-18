#pragma once
#include "cliente.h"

DWORD WINAPI envioMensagem(LPVOID param) {
	//do {

	//	SetEvent(sincControl.hEventoMensagem);
	//	WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

	//	//_tcscpy_s(sincControl.mensagem->jogador.nome, jogador.nome);
	//	//sincControl.mensagem->jogador.barreira.coord.x = jogador.barreira.coord.x;
	//	//sincControl.mensagem->jogador.barreira.coord.y = jogador.barreira.coord.y;

	/////*	debug
	////	_tprintf(TEXT("*/[Thread: %d] Envio Mensagem: Jogador: '%s'=(%d,%d) | termina: %d\n"), GetCurrentThreadId(), sincControl.mensagem->jogador.nome, sincControl.mensagem->jogador.barreira.coord.x, sincControl.mensagem->jogador.barreira.coord.y, sincControl.mensagem->termina);

	//	//Sleep(VEL_JOGO);


	//	ReleaseMutex(sincControl.hMutexMensagem);
	//	ResetEvent(sincControl.hEventoMensagem);

	//} while (!sincControl.mensagem->termina);
	return 0;
}

DWORD WINAPI recebeJogo(LPVOID param) {
	//while (!sincControl.mensagem->termina) {

	//	WaitForSingleObject(sincControl.hEventoJogo, INFINITE);
	//	WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

	//	if (sincControl.jogo->bola.coordAnt.y < LINHAS) {
	//		gotoxy(sincControl.jogo->bola.coordAnt.x, sincControl.jogo->bola.coordAnt.y);
	//		_tprintf(TEXT(" "));
	//		gotoxy(sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
	//		_tprintf(TEXT("*"));
	//	}
	//	else {
	//		//	gotoxy(sincControl.jogo->bola.coord.x , sincControl.jogo->bola.coord.y);
	//		_tprintf(TEXT("_"));
	//	}
	//	// limpar a posição anteriro não esta a funcionar
	//	gotoxy(sincControl.jogo->jogador.barreira.coordAnt.x, LINHAS);
	//	_tprintf(TEXT("       "));
	//	//limpa a barreira canto esquerdo
	//	gotoxy(0, LINHAS);
	//	_tprintf(TEXT("|                                        ")); //nao apagar isto
	//	gotoxy(sincControl.jogo->jogador.barreira.coord.x, LINHAS);
	//	_tprintf(TEXT("_____"));

	//	gotoxy(COLUNAS + 3, 2);
	//	_tprintf(TEXT("Jogador: %s"), sincControl.jogo->jogador.nome);
	//	gotoxy(COLUNAS + 3, 3);
	//	_tprintf(TEXT("Bola (x,y)=(%.2d, %.2d)"), sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
	//	gotoxy(COLUNAS + 3, 4);
	//	_tprintf(TEXT("Barreira (xp, yp)=(%.2d, %.2d)"), sincControl.jogo->jogador.barreira.coord.x, LINHAS);

	//	// debug
	//	/*_tprintf(TEXT("[Thread: %d] Recebo Jogo: Jogador: '%s' (x,y)=(%d, %d) | Bola (x,y)=(%d, %d) | termina: %d\n"), GetCurrentThreadId(), sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, sincControl.jogo->termina);
	//	Sleep(VEL_JOGO);*/

	//	ReleaseMutex(sincControl.hMutexJogo);

	//}
	return 0;
}
