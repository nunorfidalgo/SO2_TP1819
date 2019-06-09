#include "servidor.h"
#include "funcs.h"


extern BOLA bola;
extern SincControl sincControl;
extern SincPipes sincPipes;
extern MENSAGEM mensagem;

DWORD WINAPI threadRecebeMensagens(LPVOID param) {
	recebeMensagens(sincControl);

	//while (1) {
	//	recebeMensagensPipes(sincPipes, &mensagem);
	//}
	return 0;
}

DWORD WINAPI threadEnviaJogo(LPVOID param) {
	enviaJogo(sincControl, bola);

	//while (1) {
	//	enviaJogoPipe(sincPipes, &bola);
	//}
	return 0;
}

DWORD WINAPI threadBola(LPVOID param) {

	//bola.coord.x = COLUNAS / 2;
	//bola.coord.y = LINHAS - 1;
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