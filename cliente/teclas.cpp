#include "cliente.h"

extern JOGADOR jogador;
extern SincControl sincControl;

void teclas() {
	// barreira do jogador, posição inicial da barreira e posição anterior
	jogador.barreira.coord.x = 1;
	jogador.barreira.coord.y = LINHAS;
	TCHAR key_input;
	while (!sincControl.mensagem->termina) {
		key_input = _gettch();
		key_input = toupper(key_input);
		_flushall();
		switch (key_input) {
		case 77: //direta
			if (jogador.barreira.coord.x < COLUNAS - 5) {
				jogador.barreira.coord.x += 5;
			}
			break;
		case 75: // esquerda
			if (jogador.barreira.coord.x > 1) {
				jogador.barreira.coord.x -= 5;
			}
			break;
		case 27: // ESC = sair
			sincControl.mensagem->termina = 1;
			WaitForSingleObject(sincControl.hMutexJogo, INFINITE);
			gotoxy(0, LINHAS + 2);
			_tprintf(TEXT("Jogador cancelou do jogo...\n"));
			ReleaseMutex(sincControl.hMutexJogo);
			//exit(0);
			break;
		}
	}
}