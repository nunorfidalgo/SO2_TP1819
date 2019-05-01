#include "bridge.h"
#include "com.h"

extern "C" {

	/*Pacote *CriaMemPartCom(HANDLE &hMapMem) {
		hMapMem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(Pacote), MAP_MEM);
		if (hMapMem == NULL) {
			_tprintf(TEXT("Erro ao criar memoria partilhada de forma a iniciar novo jogo. (código=%d)\n"), GetLastError());
			exit(1);
		}
		return (Pacote *)MapViewOfFile(hMapMem, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Pacote));
	}

	Pacote *AcedeMemPartCom(HANDLE &hMapMem) {
		hMapMem = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, MAP_MEM);
		if (hMapMem == NULL) {
			_tprintf(TEXT("Erro ao aceder à memoria partilhada do jogo! (código=%d)\n"), GetLastError());
			_tprintf(TEXT("Por favor inicie o servidor...\n"));
			exit(1);
		}
		return (Pacote *)MapViewOfFile(hMapMem, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Pacote));
	}*/

}