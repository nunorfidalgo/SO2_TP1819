#include "bridge.h"

extern "C" {

	void CriaMemoriaPartilhadaJogo() {
		_tprintf(TEXT("Bridge - Fun��o: CriaMemoriaPartilhadaJogo!\n"));
	}

	void AcedeMemoriaPartilhadaJogo() {
		_tprintf(TEXT("Bridge - Fun��o: AcedeMemoriaPartilhadaJogo!\n"));
	}

	void gotoxy(int x, int y) {
		static HANDLE hStdout = NULL;
		COORD coord;
		coord.X = x;
		coord.Y = y;
		if (!hStdout)
			hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hStdout, coord);
	}

}