#include "servidor.h"
#include "globals.h"
#include "funcs.h"

TOPTEN topten;
SECURITY_ATTRIBUTES sa;

extern HANDLE hTMensagens, hTJogo, hTBola, hTEscutaPipes;
extern DWORD hTMensagensId, hTJogoId, hTBolaId, hTEscutaPipesId;

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("%s: Pronto...\n"), SERVIDOR);
	Seguranca(&sa);

	if (verificaInstancia())
		return -1;

	instalaServico();
	leConfig(argc, argv);
	mostraConfig(jogo);

	initWaitableTimer(sincControl, jogo);

	leRegisto(topten);

	if (!AcessoMensagensServidor(sincControl))
		return -1;

	if (!AcessoJogoServidor(sincControl))
		return -1;

	_tprintf(TEXT("%s: Espera nome jogador...\n"), SERVIDOR);
	hLogin = CreateEvent(NULL, TRUE, FALSE, TEXT("LOGIN"));
	if (hLogin == NULL) {
		_tprintf(TEXT("%s: [ERRO] Criação evento do login (%d)\n"), SERVIDOR, GetLastError());
		return -1;
	}

	WaitForSingleObject(hLogin, INFINITE);
	_tprintf(TEXT("[Thread: %d] Jogador: '%s'=(%d,%d) | termina: %d\n"), GetCurrentThreadId(), sincControl.mensagem->jogador.nome, sincControl.mensagem->jogador.barreira.coord.x, sincControl.mensagem->jogador.barreira.coord.y, sincControl.mensagem->termina);
	_tprintf(TEXT("%s: O jogo começou...\n"), SERVIDOR);
	CloseHandle(hLogin);

	/*
	* Pipes
	*/
	if (!AcessoPipesMensagensServidor(sincPipes))
		return -1;
	if (!AcessoPipesJogoServidor(sincPipes))
		return -1;
	//sincPipes.termina = 0;
	//hTEscutaPipes = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadEscutaPipes, NULL, 0, &hTEscutaPipesId);
	//if (hTEscutaPipes == NULL) {
	//	_tprintf(TEXT("%s: [Erro: %d] Ao criar a thread[%d] de escutar pipes...\n"), SERVIDOR, GetLastError(), hTEscutaPipesId);
	//	return -1;
	//}

	hTMensagens = CreateThread(NULL, 0, threadRecebeMensagens, NULL, 0, &hTMensagensId);
	if (hTMensagens == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao criar a thread[%d] das mensagens...\n"), SERVIDOR, GetLastError(), hTMensagensId);
		return -1;
	}

	hTJogo = CreateThread(NULL, 0, threadEnviaJogo, NULL, 0, &hTJogoId);
	if (hTJogo == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao criar a thread[%d] do jogo...\n"), SERVIDOR, GetLastError(), hTJogoId);
		return -1;
	}

	hTBola = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadBola, NULL, 0, &hTBolaId);
	if (hTBola == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao criar a thread[%d] da bola...\n"), SERVIDOR, GetLastError(), hTBolaId);
		return -1;
	}

	if ((WaitForSingleObject(hTEscutaPipes, INFINITE)) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] de escutar pipes...\n"), SERVIDOR, GetLastError(), hTEscutaPipesId);
	}

	if (WaitForSingleObject(hTMensagens, INFINITE) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das mensagens...\n"), SERVIDOR, GetLastError(), hTMensagensId);
	}
	if ((WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] do jogo...\n"), SERVIDOR, GetLastError(), hTJogoId);
	}
	if ((WaitForSingleObject(hTBola, INFINITE)) == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] da bola...\n"), SERVIDOR, GetLastError(), hTBolaId);
	}

	if (escreveRegisto(topten) == -1) {
		_tprintf(TEXT("%s: [Erro: %d] Impossibilidade de salvar dados no registo!\n"), SERVIDOR, GetLastError());
	}

	_tprintf(TEXT("%s: [LastError %d] terminou...\n"), SERVIDOR, GetLastError());

	closePipes(sincPipes);
	closeSincControl(sincControl);
	CloseHandle(hTMensagens);
	CloseHandle(hTJogo);
	CloseHandle(hTBola);
	CloseHandle(hServidor);
	apagaServico();
	apagaRegisto();
	_tprintf(TEXT("%s: Servidor terminado ordeiramente...\n"), SERVIDOR);
	return 0;
}

bool verificaInstancia() {
	hServidor = CreateEventW(NULL, TRUE, FALSE, SERVIDOR);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hServidor);
		hServidor = NULL;
		_tprintf(TEXT("%s: [Erro: %d]Já exite uma instância do servidor a correr...\n"), SERVIDOR, GetLastError());
		return true;
	}
	return false;
}
