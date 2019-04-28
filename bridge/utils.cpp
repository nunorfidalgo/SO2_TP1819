#include "bridge.h"

extern "C" {

	//void CriaMemoriaPartilhadaJogo() {
	//	_tprintf(TEXT("Bridge - Função: CriaMemoriaPartilhadaJogo!\n"));

	//}

	//int AcedeMemoriaPartilhadaJogo() {
	//	JOGADOR* shm;
	//	HANDLE hMemoria;

	//	TCHAR NomeMemoria[] = TEXT("Nome da Memória Partilhada");

	//	_tprintf(TEXT("Bridge - Função: AcedeMemoriaPartilhadaJogo!\n"));
	//	hMemoria = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(JOGADOR), NomeMemoria);
	//	if (hMemoria == NULL /*|| PodeLer == NULL || hMemoria == NULL*/) {
	//		_tprintf(TEXT("[Erro]Criação de objectos do Windows(%d)\n"), GetLastError());
	//		return -1;
	//	}
	//	shm = (JOGADOR*)MapViewOfFile(hMemoria, FILE_MAP_WRITE, 0, 0, sizeof(JOGADOR));
	//	if (shm == NULL) {
	//		_tprintf(TEXT("[Erro]Mapeamento da memória partilhada(%d)\n"), GetLastError());
	//		return -1;
	//	}
	//	return 0;
	//}

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