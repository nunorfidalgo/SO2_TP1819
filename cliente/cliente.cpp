#include "cliente.h"
#include "globals.h"
#include "funcs.h"

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("%s: Pronto...\n"), CLIENTE);

	if (!AcessoMensagensCliente(sincControl)) {
		return -1;
	}

	if (!AcessoJogoCliente(sincControl)) {
		return -1;
	}

	hLogin = OpenEvent(FILE_MAP_WRITE, FALSE, LOGIN);
	if (hLogin == NULL) {
		_tprintf(TEXT("%s: [ERRO] Criação evento do login (%d)\n"), CLIENTE, GetLastError());
		exit(-1);
	}

	entrar();

	SetEvent(hLogin);
	ResetEvent(hLogin);
	CloseHandle(hLogin);

	imprimeJogo();

	hTMensagens = CreateThread(NULL, 0, threadEnvioMensagem, NULL, 0, &hTMensagensId);
	if (hTMensagens == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
		return -1;
	}

	hTJogo = CreateThread(NULL, 0, threadRecebeJogo, NULL, 0, &hTJogoId);
	if (hTJogo == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
		return -1;
	}

	htTeclas = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTeclas, NULL, 0, &htTeclasId);
	if (htTeclas == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das teclas...\n"), CLIENTE, GetLastError(), htTeclasId);
		return -1;
	}

	if (WaitForSingleObject(hTMensagens, INFINITE) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
	}
	if ((WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
	}
	if ((WaitForSingleObject(htTeclas, INFINITE)) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das teclas...\n"), CLIENTE, GetLastError(), htTeclasId);
	}

	_tprintf(TEXT("%s: [LastError: %d] terminou...\n"), CLIENTE, GetLastError());

	closeSincControl(sincControl);
	CloseHandle(hTMensagens);
	CloseHandle(hTJogo);
	CloseHandle(htTeclas);
	return 0;
}