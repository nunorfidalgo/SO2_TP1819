#include "stdafx.h"
//#include "globals.h"
#include "funcs.h"

extern JOGADOR jogador;
extern BOLA bola;
extern SincControl sincControl;

DWORD WINAPI threadEnvioMensagem(LPVOID param) {
	jogador.barreira.coord.x = 180;
	enviaMensagem(sincControl, jogador);
	return 0;
}

DWORD WINAPI threadRecebeJogo(LPVOID param) {
	while (!sincControl.mensagem->termina) {
		recebeJogo(sincControl, bola);
		InvalidateRect(GetActiveWindow(), NULL, TRUE);
	}
	return 0;
}
