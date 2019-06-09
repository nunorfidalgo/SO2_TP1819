#include "bridge.h"

extern "C" {

	void enviaMensagemMemPart(SincControl &sincControl, JOGADOR &jogador) {

		SetEvent(sincControl.hEventoMensagem);
		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		_tcscpy_s(sincControl.mensagem->jogador.nome, jogador.nome);
		sincControl.mensagem->jogador.barreira.coord.x = jogador.barreira.coord.x;
		sincControl.mensagem->jogador.barreira.coord.y = jogador.barreira.coord.y;

		ReleaseMutex(sincControl.hMutexMensagem);
		ResetEvent(sincControl.hEventoMensagem);
	}

	void recebeMensagensMemPart(SincControl &sincControl) {

		WaitForSingleObject(sincControl.hEventoMensagem, INFINITE);
		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		_tcscpy_s(sincControl.jogo->jogadores[0].nome, sincControl.mensagem->jogador.nome);
		sincControl.jogo->jogadores[0].barreira.coord.x = sincControl.mensagem->jogador.barreira.coord.x;
		sincControl.jogo->jogadores[0].barreira.coord.y = sincControl.mensagem->jogador.barreira.coord.y;
		sincControl.jogo->termina = sincControl.mensagem->termina;
		//_tprintf(TEXT("%s: [Thread: %d] Mensagem recebida: Jogador: '%s' (x,y)=(%d, %d) | Bola (x,y)=(%d, %d) | termina: %d\n"), SERVIDOR, GetCurrentThreadId(), sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, sincControl.jogo->termina);

		ReleaseMutex(sincControl.hMutexMensagem);
	}

	bool enviaMensagemPipe(HANDLE hPipe, MENSAGEM *mensagem) {
		DWORD nBytesEnviados;
		if (!WriteFile(hPipe, mensagem, sizeof(MENSAGEM), &nBytesEnviados, NULL))
			return false;
		else
			return true;
	}

	bool recebeMensagensPipes(SincPipes &sincPipes, MENSAGEM *mensagem) {
		int i;
		do {

			WaitForSingleObject(sincPipes.hMutex, INFINITE);

			for (i = 0; i < N_PIPES; i++) {

				if (sincPipes.hPipes[i].activo) {

					if (!ReadFile(&sincPipes.hPipes[i], mensagem, sizeof(MENSAGEM), &sincPipes.nBytesRecebidos, NULL)) {
						_tprintf(TEXT("%s: ERROR [%d] (ReadFile) ao ler do pipe!\n"), SERVIDOR, GetLastError());
						break;
						return false;
					}

				}
			}

			ReleaseMutex(sincPipes.hMutex);

		} while (1); /* (!sincPipes.termina);*/

		sincPipes.termina = 1;

		for (i = 0; i < N_PIPES; i++)
			SetEvent(sincPipes.hEvent[i]);

		return true;
	}

}