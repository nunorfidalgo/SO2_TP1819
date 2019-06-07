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
		while (!sincControl.mensagem->termina) {

			WaitForSingleObject(sincControl.hEventoMensagem, INFINITE);
			WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

			_tcscpy_s(sincControl.jogo->jogador.nome, sincControl.mensagem->jogador.nome);
			sincControl.jogo->jogador.barreira.coord.x = sincControl.mensagem->jogador.barreira.coord.x;
			sincControl.jogo->jogador.barreira.coord.y = sincControl.mensagem->jogador.barreira.coord.y;
			sincControl.jogo->termina = sincControl.mensagem->termina;

			//_tprintf(TEXT("%s: [Thread: %d] Mensagem recebida: Jogador: '%s' (x,y)=(%d, %d) | Bola (x,y)=(%d, %d) | termina: %d\n"), SERVIDOR, GetCurrentThreadId(), sincControl.jogo->jogador.nome, sincControl.jogo->jogador.barreira.coord.x, sincControl.jogo->jogador.barreira.coord.y, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, sincControl.jogo->termina);

			ReleaseMutex(sincControl.hMutexMensagem);
		}

	}

	void enviaMensagemPipe(HANDLE hPipe, MENSAGEM *mensagem) {
		DWORD nBytesEnviados;
		WriteFile(hPipe, mensagem, sizeof(MENSAGEM), &nBytesEnviados, NULL);
	}

	void escutaMensagensPipes(SincPipes &sincPipes) {
		int i;

		_tprintf(TEXT("%s: Escuta de mensagens dos clientes...\n"), SERVIDOR);

		while (!sincPipes.termina && sincPipes.numClientes < N_PIPES) {

			_tprintf(TEXT("%s: Esperar ligação de um jogador...\n"), SERVIDOR);

			sincPipes.pipeNumber = WaitForMultipleObjects(N_PIPES, sincPipes.hEvent, FALSE, INFINITE);
			i = sincPipes.pipeNumber - WAIT_OBJECT_0;

			_tprintf(TEXT("%s: Jogador ligado no pipe: %d\n"), SERVIDOR, i);

			if (i >= 0 && i < N_PIPES)
			{
				if (!GetOverlappedResult(sincPipes.hPipes[i].hInstance, &sincPipes.hPipes[i].overlap, &sincPipes.nBytesRecebidos, FALSE)) {
					_tprintf(TEXT("%s: [ERRO] obter resultados do pipe: %d \n"), SERVIDOR, i);
					continue;
				}

				ResetEvent(sincPipes.hEvent[i]);
				WaitForSingleObject(sincPipes.hMutex, INFINITE);

				sincPipes.hPipes[i].activo = TRUE;

				ReleaseMutex(sincPipes.hMutex);
				sincPipes.numClientes++;
			}

		}
	}

	void recebeMensagensPipes(SincPipes &sincPipes, MENSAGEM *mensagem) {
		int i;
		BOOL recebido;
		do {

			WaitForSingleObject(sincPipes.hMutex, INFINITE);

			for (i = 0; i < N_PIPES; i++) {
				if (sincPipes.hPipes[i].activo) {
					recebido = ReadFile(&sincPipes.hPipes[i], mensagem, sizeof(MENSAGEM), &sincPipes.nBytesRecebidos, NULL);
					if (!recebido || !sincPipes.nBytesRecebidos) {
						_tprintf(TEXT("%s: Jogador: '%s' %d... (ReadFile)\n"), SERVIDOR, mensagem->jogador.nome, sincPipes.nBytesRecebidos);
						break;
					}
				}
			}

			ReleaseMutex(sincPipes.hMutex);

		} while (!sincPipes.termina);

		/*sincPipes.termina = 1;*/

		for (i = 0; i < N_PIPES; i++)
			SetEvent(sincPipes.hEvent[i]);
	}

}