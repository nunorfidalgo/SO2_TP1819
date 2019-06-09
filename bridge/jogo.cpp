﻿#include "bridge.h"

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


	void enviaJogoPipe(SincPipes& sincPipes, BOLA* bola) { // servidor envia para cliente, em vez de bola devia ser JOGO!!
		//_tprintf(TEXT("%s: Bola: (%d, %d), direção: (%d, %d)\n"), SERVIDOR, bola->coord.x, bola->coord.y, bola->direcao.x, bola->direcao.y);
		int i;
		WaitForSingleObject(sincPipes.hMutex, INFINITE);

		for (i = 0; i < N_PIPES; i++) {
			if (sincPipes.hPipes[i].activo) {
				if (!WriteFile(sincPipes.hPipes[i].hInstance, bola, sizeof(BOLA), &sincPipes.nBytesEnviados, NULL)) {
					_tprintf(TEXT("%s: ERROR [%d] (WriteFile) Escrever no pipe!\n"), SERVIDOR, GetLastError());
					/*exit(-1);*/
					break;
				}
			}
		}

		ReleaseMutex(sincPipes.hMutex);

	}

	bool recebeJogoPipe(HANDLE hPipe, BOLA* bola) { // Cliente
		if (!ReadFile(hPipe, bola, sizeof(BOLA), NULL, NULL))
			return false;
		return true;
	}



}
