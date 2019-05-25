#include "cliente.h"
#include "funcs.h"

extern JOGADOR jogador;
extern SincControl sincControl;

DWORD WINAPI threadEnvioMensagem(LPVOID param) {
	enviaMensagem(sincControl, jogador);
	return 0;
}

DWORD WINAPI threadRecebeJogo(LPVOID param) {
	recebeJogo(sincControl);
	return 0;
}

DWORD WINAPI threadTeclas(LPVOID param) {
	teclas();
	return 0;
}