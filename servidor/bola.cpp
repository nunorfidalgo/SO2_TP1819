#include "servidor.h"

extern BOLA bola;
extern SincControl sincControl;

void MovimentoBola() {

	while (!sincControl.jogo->termina) {

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
		Sleep(VEL_JOGO); // waitable timer
	}
}