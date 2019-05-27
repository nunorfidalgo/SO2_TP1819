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

			//_tprintf(TEXT("[Thread: %d] Envio Jogo [%d] Jogador: '%s' (x,y)=(%d, %d) | Bola (x,y)=(%d, %d) | termina: %d\n"), GetCurrentThreadId(), j, sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, sincControl.jogo->termina);
			//j++;

			Sleep(VEL_JOGO);

			ReleaseMutex(sincControl.hMutexJogo);
			ResetEvent(sincControl.hEventoJogo);

		}
	}

	void recebeJogo(SincControl &sincControl, BOLA &bola) {
		while (!sincControl.mensagem->termina) {

			WaitForSingleObject(sincControl.hEventoJogo, INFINITE);
			WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

			bola.coord.x = sincControl.jogo->bola.coord.x;
			bola.coord.y = sincControl.jogo->bola.coord.y;

			ReleaseMutex(sincControl.hMutexJogo);

		}
	}


}
