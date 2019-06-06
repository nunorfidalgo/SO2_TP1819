#include "bridge.h"

extern "C" {

	void enviaMensagem(SincControl& sincControl, JOGADOR& jogador) {

		SetEvent(sincControl.hEventoMensagem);
		WaitForSingleObject(sincControl.hMutexMensagem, INFINITE);

		_tcscpy_s(sincControl.mensagem->jogador.nome, jogador.nome);
		sincControl.mensagem->jogador.barreira.coord.x = jogador.barreira.coord.x;
		sincControl.mensagem->jogador.barreira.coord.y = jogador.barreira.coord.y;

		ReleaseMutex(sincControl.hMutexMensagem);
		ResetEvent(sincControl.hEventoMensagem);
	}

	void recebeMensagens(SincControl& sincControl) {
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

}


//int pipeLeitor() {
//	TCHAR buf[256];
//	HANDLE hPipe;
//	int i = 0;
//	BOOL ret;
//	DWORD n;
//
//	_tprintf(TEXT("[LEITOR] Esperar pelo pipe '%s' (WaitNamedPipe)\n"), PIPE_NAME);
//	if (!WaitNamedPipe(PIPE_NAME, NMPWAIT_WAIT_FOREVER)) {
//		_tprintf(TEXT("[ERRO] Ligar ao pipe '%s'! (WaitNamedPipe)\n"), PIPE_NAME);
//		exit(-1);
//	}
//	_tprintf(TEXT("[LEITOR] Ligação ao pipe do escritor... (CreateFile)\n"));
//	hPipe = CreateFile(PIPE_NAME, GENERIC_READ, 0, NULL, OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL, NULL);
//	if (hPipe == NULL) {
//		_tprintf(TEXT("[ERRO] Ligar ao pipe '%s'! (CreateFile)\n"), PIPE_NAME);
//		exit(-1);
//	}
//	_tprintf(TEXT("[LEITOR] Liguei-me...\n"));
//	while (1) {
//		ret = ReadFile(hPipe, buf, sizeof(buf), &n, NULL);
//		buf[n / sizeof(TCHAR)] = '\0';
//		if (!ret || !n) {
//			_tprintf(TEXT("[LEITOR] %d %d... (ReadFile)\n"), ret, n);
//			break;
//		}
//		_tprintf(TEXT("[LEITOR] Recebi %d bytes: '%s'... (ReadFile)\n"), n, buf);
//	}
//	CloseHandle(hPipe);
//	Sleep(200);
//	return 0;
//}
//
//
//int pipeEscritor() {
//
//	// mutex
//	hMutex = CreateMutex(
//		NULL,              // default security attributes
//		FALSE,             // initially not owned
//		TEXT("ex3-escritor"));      // unnamed mutex
//	if (hMutex == NULL) {
//		_tprintf(TEXT("CreateMutex error: %d\n"), GetLastError());
//		return 1;
//	}
//
//	for (i = 0; i < N; i++) {
//		_tprintf(TEXT("[ESCRITOR] Criar uma cópia do pipe '%s' ... (CreateNamedPipe)\n"), PIPE_NAME);
//
//		hEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
//
//		hPipes[i].hInstance = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED, PIPE_WAIT |
//			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, N, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR), 1000, NULL);
//
//		if (hPipes[i].hInstance == INVALID_HANDLE_VALUE) {
//			_tprintf(TEXT("[ERRO] Criar Named Pipe! (CreateNamedPipe)\n"));
//			exit(-1);
//		}
//
//		ZeroMemory(&hPipes[i].overlap, sizeof(hPipes[i].overlap));
//		hPipes[i].overlap.hEvent = hEvent[i];
//
//		_tprintf(TEXT("[ESCRITOR] Esperar ligação overlapped de um leitor...(ConnectNamedPipe)\n"));
//
//		if (ConnectNamedPipe(hPipes[i].hInstance, &hPipes[i].overlap) != 0) {
//			_tprintf(TEXT("[ERRO] Ligação ao leitor! (ConnectNamedPipe\n"));
//			break;
//		}
//
//		hPipes[i].activo = FALSE;
//
//	}
//
//	hT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadConsola, NULL, 0, NULL);
//	if (hT != NULL)
//		_tprintf(TEXT("Lancei uma thread...\n"));
//	else
//		_tprintf(TEXT("Erro ao criar Thread\n"));
//
//	while (!end && numClientes < N) {
//
//		_tprintf(TEXT("[ESCRITOR] Esperar ligação de um leitor...\n"));
//
//		x = WaitForMultipleObjects(N, hEvent, FALSE, INFINITE);
//		i = x - WAIT_OBJECT_0;
//
//		_tprintf(TEXT("[ESCRITOR] New i = %d \n"), i);
//
//		if (i >= 0 && i < N) {
//			if (!GetOverlappedResult(hPipes[i].hInstance, &hPipes[i].overlap, &n, FALSE)) {
//				_tprintf(TEXT("[ERRO] obter resultados de %d \n"), i);
//				continue;
//			}
//
//			ResetEvent(hEvent[i]);
//			WaitForSingleObject(hMutex, INFINITE);
//			hPipes[i].activo = TRUE;
//			ReleaseMutex(hMutex);
//			numClientes++;
//		}
//
//	}
//
//	WaitForSingleObject(hT, INFINITE);
//
//	_tprintf(TEXT("[ESCRITOR] Desligar o pipe (DisconnectNamedPipe)\n"));
//	for (i = 0; i < N; i++) {
//		SetEvent(hEvent[i]);
//		if (!DisconnectNamedPipe(hPipes[i].hInstance)) {
//			_tprintf(TEXT("[ERRO] Desligar o pipe! (DisconnectNamedPipe)\n"));
//			exit(-1);
//		}
//		CloseHandle(hPipes[i].hInstance);
//		CloseHandle(hEvent[i]);
//	}
//
//	Sleep(2000);
//	exit(0);
//}