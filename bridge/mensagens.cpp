#include "bridge.h"

extern "C" {

	void enviaMensagem(SincControl &sincControl, JOGADOR &jogador) {
		do {

			SetEvent(sincControl.hEventoMensagem);
			WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

			_tcscpy_s(sincControl.mensagem->jogador.nome, jogador.nome);
			sincControl.mensagem->jogador.barreira.coord.x = jogador.barreira.coord.x;
			sincControl.mensagem->jogador.barreira.coord.y = jogador.barreira.coord.y;

			//debug
			//_tprintf(TEXT("[Thread: %d] Envio Mensagem: Jogador: '%s'=(%d,%d) | termina: %d\n"), GetCurrentThreadId(), sincControl.mensagem->jogador.nome, sincControl.mensagem->jogador.barreira.coord.x, sincControl.mensagem->jogador.barreira.coord.y, sincControl.mensagem->termina);

			Sleep(VEL_JOGO);

			ReleaseMutex(sincControl.hMutexMensagem);
			ResetEvent(sincControl.hEventoMensagem);

		} while (!sincControl.mensagem->termina);
	}

	void recebeMensagens(SincControl &sincControl) {
		int m = 1;

		while (!sincControl.mensagem->termina) {

			WaitForSingleObject(sincControl.hEventoMensagem, INFINITE);
			WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

			//_tprintf(TEXT("[Thread: %d] Recebi Mensagem [%d]: Jogador: '%s'=(%d,%d) | termina: %d\n"), GetCurrentThreadId(), m, sincControl.mensagem->jogador.nome, sincControl.mensagem->jogador.barreira.coord.x, sincControl.mensagem->jogador.barreira.coord.y, sincControl.mensagem->termina);

			_tcscpy_s(sincControl.jogo->jogador.nome, sincControl.mensagem->jogador.nome);
			sincControl.jogo->jogador.barreira.coord.x = sincControl.mensagem->jogador.barreira.coord.x;
			sincControl.jogo->jogador.barreira.coord.y = sincControl.mensagem->jogador.barreira.coord.y;
			sincControl.jogo->termina = sincControl.mensagem->termina;
			m++;

			ReleaseMutex(sincControl.hMutexMensagem);

		}

	}

}