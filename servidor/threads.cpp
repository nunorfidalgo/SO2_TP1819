#include "servidor.h"
#include "funcs.h"

extern BOLA bola;
extern SincControl sincControl;

DWORD WINAPI threadRecebeMensagens(LPVOID param) {
	recebeMensagens(sincControl);
	return 0;
}

DWORD WINAPI threadEnviaJogo(LPVOID param) {
	enviaJogo(sincControl, bola);
	return 0;
}

DWORD WINAPI threadBola(LPVOID param) {
	bola.coord.x = COLUNAS / 2;
	bola.coord.y = LINHAS - 1;
	bola.coordAnt.x = bola.coord.x;
	bola.coordAnt.y = bola.coord.y;
	bola.direcao.x = 1;
	bola.direcao.y = 1;
	MovimentoBola();
	return 0;
}