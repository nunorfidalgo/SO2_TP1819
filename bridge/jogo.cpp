#include "bridge.h"

extern "C" {

	void enviaJogo(SincControl& sincControl, BOLA& bola) {
		int j = 1;
		while (!sincControl.jogo->termina) {

			SetEvent(sincControl.hEventoJogo);
			WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

			WaitForSingleObject(sincControl.hTimer, INFINITE); // waitable timer

			sincControl.jogo->bola.coord.x = bola.coord.x;
			sincControl.jogo->bola.coord.y = bola.coord.y;

			ReleaseMutex(sincControl.hMutexJogo);
			ResetEvent(sincControl.hEventoJogo);
		}
	}

	void recebeJogo(SincControl& sincControl, BOLA& bola) {

		WaitForSingleObject(sincControl.hEventoJogo, INFINITE);
		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);

		bola.coord.x = sincControl.jogo->bola.coord.x;
		bola.coord.y = sincControl.jogo->bola.coord.y;

		ReleaseMutex(sincControl.hMutexJogo);
	}


}
