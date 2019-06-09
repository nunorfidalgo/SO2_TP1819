#include "servidor.h"
#include "funcs.h"

extern BOLA bola;
extern SincControl sincControl;
extern SincPipes sincPipesMensagens;
extern SincPipes sincPipesJogo;
extern MENSAGEM mensagem;

DWORD WINAPI threadRecebeMensagens(LPVOID param) {
	//recebeMensagensMemPart(sincControl);

	/*mensagem.termina = 0;*/
	//recebeMensagensPipes(sincPipesMensagens, &mensagem);

	return 0;
}

DWORD WINAPI threadEnviaJogo(LPVOID param) {
	//enviaJogoMemPart(sincControl, bola);
	enviaJogoPipe(sincPipesJogo, &bola);
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

DWORD WINAPI threadEscutaMensagens(LPVOID param) {
	//escutaMensagensPipes(sincPipesMensagens);
	escutaMensagensPipes(sincPipesJogo);
	return 0;
}
