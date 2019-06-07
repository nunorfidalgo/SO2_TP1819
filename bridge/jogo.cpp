#include "bridge.h"

extern "C" {

	void enviaJogoMemPart(SincControl &sincControl, BOLA &bola) {
		int j = 1;
		while (!sincControl.jogo->termina) {

			SetEvent(sincControl.hEventoJogo);
			WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

			WaitForSingleObject(sincControl.hTimer, INFINITE); // waitable timer

			sincControl.jogo->bola.coord.x = bola.coord.x;
			sincControl.jogo->bola.coord.y = bola.coord.y;

			//_tprintf(TEXT("[Thread: %d] Envio Jogo [%d] Jogador: '%s' (x,y)=(%d, %d) | Bola (x,y)=(%d, %d) | termina: %d\n"), GetCurrentThreadId(), j, sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, sincControl.jogo->termina);
			//j++;

			ReleaseMutex(sincControl.hMutexJogo);
			ResetEvent(sincControl.hEventoJogo);
		}
	}

	void recebeJogoMemPart(SincControl &sincControl, BOLA &bola) {

		WaitForSingleObject(sincControl.hEventoJogo, INFINITE);
		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

		bola.coord.x = sincControl.jogo->bola.coord.x;
		bola.coord.y = sincControl.jogo->bola.coord.y;

		ReleaseMutex(sincControl.hMutexJogo);
	}

	//void enviaJogoPipe(SincPipes &sincPipes, BOLA &bola) {

	//}

	//void recebeJogoPipe(SincPipes &sincPipes, BOLA &bola) {

	//}


}
