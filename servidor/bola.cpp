#include "servidor.h"

extern JOGO jogo;
extern WAIT_TIMER waitTimer;

void MovimentoBola() {

	while (/*!sincControl.jogo->termina*/ 1) {

		jogo.bola.coord.x -= jogo.bola.direcao.x;
		jogo.bola.coord.y -= jogo.bola.direcao.y;

		if (jogo.bola.coord.x > _WINDOW_WIDTH - 30 || jogo.bola.coord.x < 0) { // limites direita e esquerda
			jogo.bola.direcao.x *= -1;
		}
		//if (bola.coord.y > _WINDOW_HEIGHT - 78 || bola.coord.y < 0) { // limites inferior e superior
		if (jogo.bola.coord.y < 1) { // limite superior
			jogo.bola.direcao.y *= -1;
		}

		/*if (bola.coord.y > _WINDOW_HEIGHT - 78) {
			sincControl.jogo->termina = 1;
			exit(1);
		}*/

		// barreira
		if (jogo.bola.coord.y > _WINDOW_HEIGHT - 78) // limites inferior
			if (jogo.bola.coord.x >= jogo.jogadores[0].barreira.coord.x && jogo.bola.coord.x <= jogo.jogadores[0].barreira.coord.x + 90)
				jogo.bola.direcao.y *= -1;
		/*else {
			sincControl.jogo->termina = 1;
		}*/

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

		//Sleep(10); 
		WaitForSingleObject(waitTimer.hTimer, INFINITE); // waitable timer

	}
}