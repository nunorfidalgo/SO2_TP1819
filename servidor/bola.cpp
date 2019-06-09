#include "servidor.h"

extern BOLA bola;
extern SincControl sincControl;

void MovimentoBola() {

	while (!sincControl.jogo->termina) {

		bola.coord.x -= bola.direcao.x;
		bola.coord.y -= bola.direcao.y;

		if (bola.coord.x > _WINDOW_WIDTH - 30 || bola.coord.x < 0) { // limites direita e esquerda
			bola.direcao.x *= -1;
		}
		//if (bola.coord.y > _WINDOW_HEIGHT - 78 || bola.coord.y < 0) { // limites inferior e superior
		if ((bola.coord.y > _WINDOW_HEIGHT - 78 || bola.coord.y < 0)) { // limite superior
			bola.direcao.y *= -1;
		}

		/*	if (bola.coord.y > _WINDOW_HEIGHT - 78) {
					sincControl.jogo->termina = 1;
					exit(1);
			}*/

			// barreira
			//if (bola.coord.y > _WINDOW_HEIGHT - 78) // limites inferior
			//	if (bola.coord.x >= sincControl.jogo->jogador.barreira.coord.x && bola.coord.x <= sincControl.jogo->jogador.barreira.coord.x + 90)
			//		bola.direcao.y *= -1;
			/*else {
				sincControl.jogo->termina = 1;
			}*/


			/*	if (bola.coord.y > _WINDOW_HEIGHT)
					_tprintf(TEXT("Perdeu o jogo..."));
				exit(1);*/
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
		WaitForSingleObject(sincControl.hTimer, INFINITE); // waitable timer

	}
}