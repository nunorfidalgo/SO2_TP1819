#include "servidor.h"
#include "funcs.h"

extern BOLA bola;
extern SincControl sincControl;
extern SincPipes sincPipes;
extern MENSAGEM mensagem;

DWORD WINAPI threadRecebeMensagens(LPVOID param) {
	while (!sincControl.mensagem->termina || !sincPipes.termina) {
		recebeMensagensMemPart(sincControl);
		recebeMensagensPipes(sincPipes, &mensagem);
	}
	return 0;
}

DWORD WINAPI threadEnviaJogo(LPVOID param) {
	while (!sincControl.jogo->termina || !sincPipes.termina) {
		enviaJogoMemPart(sincControl, bola);
		enviaJogoPipe(sincPipes, &bola);
	}
	return 0;
}

DWORD WINAPI threadBola(LPVOID param) {
	bola.coord.x = 180;
	bola.coord.y = 520;
	bola.direcao.x = 1;
	bola.direcao.y = 1;

	MovimentoBola();

	return 0;
}

DWORD WINAPI threadEscutaPipes(LPVOID param) {
	escutaPipes(sincPipes);
	return 0;
}
