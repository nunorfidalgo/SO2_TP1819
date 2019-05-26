#include "stdafx.h"
#include "funcs.h"

extern JOGADOR jogador;
extern SincControl sincControl;

DWORD WINAPI threadEnvioMensagem(LPVOID param) {
	jogador.barreira.coord.x = 180;
	enviaMensagem(sincControl, jogador);
	return 0;
}

DWORD WINAPI threadRecebeJogo(LPVOID param) {
	recebeJogo(sincControl);
	return 0;
}