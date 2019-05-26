#include "bridge.h"
#include "sinc.h"

extern "C" {

	void gotoxy(int x, int y) {
		static HANDLE hStdout = NULL;
		COORD coord;
		coord.X = x;
		coord.Y = y;
		if (!hStdout)
			hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hStdout, coord);
	}

	void closeSincControl(SincControl &sincControl) {
		CloseHandle(sincControl.hMutexMensagem);
		CloseHandle(sincControl.hEventoMensagem);
		CloseHandle(sincControl.hMutexJogo);
		CloseHandle(sincControl.hEventoJogo);
		UnmapViewOfFile(sincControl.mensagem);
		UnmapViewOfFile(sincControl.jogo);
		CloseHandle(sincControl.hMemMensagem);
		CloseHandle(sincControl.hMemJogo);
	}

}