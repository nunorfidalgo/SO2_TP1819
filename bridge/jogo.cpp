#include "bridge.h"

extern "C" {

	void enviaJogo(SincControl &sincControl, BOLA &bola) {
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
	}

	void recebeJogo(SincControl &sincControl) {
		while (!sincControl.mensagem->termina) {

			WaitForSingleObject(sincControl.hEventoJogo, INFINITE);
			WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

			if (sincControl.jogo->bola.coordAnt.y < LINHAS) {
				gotoxy(sincControl.jogo->bola.coordAnt.x, sincControl.jogo->bola.coordAnt.y);
				_tprintf(TEXT(" "));
				gotoxy(sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
				_tprintf(TEXT("*"));
			}
			else {
				//	gotoxy(sincControl.jogo->bola.coord.x , sincControl.jogo->bola.coord.y);
				_tprintf(TEXT("_"));
			}
			// limpar a posição anteriro não esta a funcionar
			gotoxy(sincControl.jogo->jogador.barreira.coordAnt.x, LINHAS);
			_tprintf(TEXT("       "));
			//limpa a barreira canto esquerdo
			gotoxy(0, LINHAS);
			_tprintf(TEXT("|                                        ")); //nao apagar isto
			gotoxy(sincControl.jogo->jogador.barreira.coord.x, LINHAS);
			_tprintf(TEXT("_____"));

			gotoxy(COLUNAS + 3, 2);
			_tprintf(TEXT("Jogador: %s"), sincControl.jogo->jogador.nome);
			gotoxy(COLUNAS + 3, 3);
			_tprintf(TEXT("Bola (x,y)=(%.2d, %.2d)"), sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y);
			gotoxy(COLUNAS + 3, 4);
			_tprintf(TEXT("Barreira (xp, yp)=(%.2d, %.2d)"), sincControl.jogo->jogador.barreira.coord.x, LINHAS);

			// debug
			/*_tprintf(TEXT("[Thread: %d] Recebo Jogo: Jogador: '%s' (x,y)=(%d, %d) | Bola (x,y)=(%d, %d) | termina: %d\n"), GetCurrentThreadId(), sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, sincControl.jogo->termina);
			Sleep(VEL_JOGO);*/

			ReleaseMutex(sincControl.hMutexJogo);

		}
	}


}
