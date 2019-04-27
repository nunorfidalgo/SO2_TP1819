#include "bridge.h"
#include "dados.h"

extern "C" {

	void CriaMemoriaPartilhadaJogo() {
		_tprintf(TEXT("Bridge - Fun��o: CriaMemoriaPartilhadaJogo!\n"));

	}

	int AcedeMemoriaPartilhadaJogo() {
		LOGIN* shm_login;
		HANDLE hMemoria;

		
		_tprintf(TEXT("Bridge - Fun��o: AcedeMemoriaPartilhadaJogo!\n"));
		hMemoria = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(LOGIN), MEM_PART);
		if (hMemoria == NULL /*|| PodeLer == NULL || hMemoria == NULL*/) {
			_tprintf(TEXT("[Erro]Cria��o de objectos do Windows(%d)\n"), GetLastError());
			return -1;
		}
		shm_login = (LOGIN *)MapViewOfFile(hMemoria, FILE_MAP_WRITE, 0, 0, sizeof(LOGIN));
		if (shm_login == NULL) {
			_tprintf(TEXT("[Erro]Mapeamento da mem�ria partilhada(%d)\n"), GetLastError());
			return -1;
		}
		return 0;
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