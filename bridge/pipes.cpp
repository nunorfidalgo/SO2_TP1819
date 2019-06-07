#include "bridge.h"

extern "C" {

	// Mensagens
	bool AccessoPipesMensagensServidor(SincPipes &sincPipes) {
		int i;
		sincPipes.hMutex = CreateMutex(
			NULL,          // default security attributes
			FALSE,         // initially not owned
			MUTEX_PIPES);  // unnamed mutex
		if (sincPipes.hMutex == NULL) {
			_tprintf(TEXT("%s: ERRO [%d] ao criar mutex para pipes!\n"), SERVIDOR, GetLastError());
			return false;
		}

		for (i = 0; i < N_PIPES; i++) {
			_tprintf(TEXT("%s: (CreateNamedPipe [%d]) Criar uma cópia do pipe '%s' \n"), SERVIDOR, i, PIPE_NAME);

			sincPipes.hEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);

			sincPipes.hPipes[i].hInstance = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_INBOUND | FILE_FLAG_OVERLAPPED, PIPE_WAIT |
				PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, N_PIPES, sizeof(MENSAGEM), sizeof(MENSAGEM), 1000, NULL);

			if (sincPipes.hPipes[i].hInstance == INVALID_HANDLE_VALUE) {
				_tprintf(TEXT("%s: (CreateNamedPipe [%d]) ERRO [%d] ao criar Named Pipe!\n"), SERVIDOR, i, GetLastError());
				return false;
			}

			ZeroMemory(&sincPipes.hPipes[i].overlap, sizeof(sincPipes.hPipes[i].overlap));
			sincPipes.hPipes[i].overlap.hEvent = sincPipes.hEvent[i];

			_tprintf(TEXT("%s: (ConnectNamedPipe [%d]) Esperar ligação overlapped de um jogador...\n"), SERVIDOR, i);

			if (ConnectNamedPipe(sincPipes.hPipes[i].hInstance, &sincPipes.hPipes[i].overlap) != 0) {
				_tprintf(TEXT("%s: (ConnectNamedPipe [%d]) ERRO [%d] ao estabelecer ligação ao jogador!\n"), SERVIDOR, i, GetLastError());
				break;
			}

			sincPipes.hPipes[i].activo = FALSE;

		}
		return true;
	}

	void closePipes(SincPipes &sincPipes) {
		int i;
		for (i = 0; i < N_PIPES; i++) {
			_tprintf(TEXT("%s: Desligar o pipe (DisconnectNamedPipe [%d])\n"), SERVIDOR, i);
			SetEvent(sincPipes.hEvent[i]);
			if (!DisconnectNamedPipe(sincPipes.hPipes[i].hInstance)) {
				_tprintf(TEXT("%s: ERRO [%d] Desligar o pipe! (DisconnectNamedPipe [%d])\n"), SERVIDOR, GetLastError(), i);
				exit(-1);
			}
			CloseHandle(sincPipes.hPipes[i].hInstance);
			CloseHandle(sincPipes.hEvent[i]);
		}
	}

	bool AcessoPipeMensagensCliente(HANDLE &hPipe) { // exemplo leitor...

		/*_tprintf(TEXT("[LEITOR] Esperar pelo pipe '%s' (WaitNamedPipe)\n"), PIPE_NAME);*/
		if (!WaitNamedPipe(PIPE_NAME, NMPWAIT_WAIT_FOREVER)) {
			//_tprintf(TEXT("[ERRO] Ligar ao pipe '%s'! (WaitNamedPipe)\n"), PIPE_NAME);
			return false;
		}

		//_tprintf(TEXT("[LEITOR] Ligação ao pipe do escritor... (CreateFile)\n"));
		hPipe = CreateFile(PIPE_NAME, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hPipe == NULL) {
			//_tprintf(TEXT("[ERRO] Ligar ao pipe '%s'! (CreateFile)\n"), PIPE_NAME);
			return false;
		}
		return true;
	}

}
