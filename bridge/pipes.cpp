#include "bridge.h"

extern "C" {

	void escutaPipes(SincPipes &sincPipes) {
		int i;

		while (!sincPipes.termina && sincPipes.numClientes < N_PIPES) {

			_tprintf(TEXT("%s: Esperar ligação de um jogador...\n"), SERVIDOR);

			_tprintf(TEXT("%s: 2, lasterror=%d !!!!\n"), SERVIDOR, GetLastError());

			sincPipes.pipeNumber = WaitForMultipleObjects(N_PIPES, sincPipes.hEvent, FALSE, INFINITE);
			i = sincPipes.pipeNumber - WAIT_OBJECT_0;

			_tprintf(TEXT("%s: 3  !!!!\n"), SERVIDOR);

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
			_tprintf(TEXT("%s: 4  !!!!\n"), SERVIDOR);
		}
		_tprintf(TEXT("%s: 5 fim  !!!!\n"), SERVIDOR);
	}

	// Mensagens
	bool AcessoPipesMensagensServidor(SincPipes &sincPipes) {
		int i;
		sincPipes.hMutex = CreateMutex(
			NULL,          // default security attributes
			FALSE,         // initially not owned
			MUTEX_PIPES_MENSAGENS);  // unnamed mutex
		if (sincPipes.hMutex == NULL) {
			_tprintf(TEXT("%s: ERRO [%d] ao criar mutex para pipes!\n"), SERVIDOR, GetLastError());
			return false;
		}

		for (i = 0; i < N_PIPES; i++) {
			_tprintf(TEXT("%s: (CreateNamedPipe [%d]) Criar uma cópia do pipe '%s' \n"), SERVIDOR, i, PIPE_MENSAGENS);

			sincPipes.hEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);

			sincPipes.hPipes[i].hInstance = CreateNamedPipe(PIPE_MENSAGENS, PIPE_ACCESS_INBOUND | FILE_FLAG_OVERLAPPED, PIPE_WAIT |
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

	bool AcessoPipeMensagensCliente(HANDLE &hPipe) {

		if (!WaitNamedPipe(PIPE_MENSAGENS, NMPWAIT_WAIT_FOREVER)) {
			return false;
		}

		hPipe = CreateFile(PIPE_MENSAGENS, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hPipe == NULL) {
			return false;
		}
		return true;
	}

	// Jogo
	bool AcessoPipesJogoServidor(SincPipes &sincPipes) {
		int i;
		sincPipes.hMutex = CreateMutex(
			NULL,          // default security attributes
			FALSE,         // initially not owned
			MUTEX_PIPES_JOGO);  // unnamed mutex
		if (sincPipes.hMutex == NULL) {
			_tprintf(TEXT("%s: ERRO [%d] ao criar mutex para pipes!\n"), SERVIDOR, GetLastError());
			return false;
		}

		for (i = 0; i < N_PIPES; i++) {
			_tprintf(TEXT("%s: (CreateNamedPipe [%d]) Criar uma cópia do pipe '%s' \n"), SERVIDOR, i, PIPE_JOGO);

			sincPipes.hEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);

			sincPipes.hPipes[i].hInstance = CreateNamedPipe(PIPE_JOGO, PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED, PIPE_WAIT |
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

	bool AcessoPipesJogoCliente(HANDLE hPipe) {

		if (!WaitNamedPipe(PIPE_JOGO, NMPWAIT_WAIT_FOREVER)) {
			return false;
		}

		hPipe = CreateFile(PIPE_JOGO, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hPipe == NULL) {
			return false;
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

}
