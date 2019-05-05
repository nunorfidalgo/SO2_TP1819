#include "bridge.h"
#include "mensagem.h"

extern "C" {

	bool AcessoJogoServidor(SincControl &sincControl) {
		sincControl.hMutexJogo = CreateMutex(NULL, FALSE, MUTEX_JOGO);
		sincControl.hEventoJogo = CreateEvent(NULL, TRUE, FALSE, EVENTO_JOGO);
		sincControl.hMemJogo = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(JOGO), SHM_JOGO);
		if (sincControl.hMutexJogo == NULL || sincControl.hEventoJogo == NULL || sincControl.hMemJogo == NULL) {
			_tprintf(TEXT("%s: [Erro: %d] Na criação de objectos (%s)...\n"), SERVIDOR, GetLastError(), JOGO_TXT);
			return false;
		}
		sincControl.jogo = (JOGO*)MapViewOfFile(sincControl.hMemJogo, FILE_MAP_WRITE, 0, 0, sizeof(JOGO));
		if (sincControl.jogo == NULL) {
			_tprintf(TEXT("%s: [Erro: %d] No mapeamento da memória partilhada (%s)\n"), SERVIDOR, GetLastError(), JOGO_TXT);
			return false;
		}
		return true;
	}

	bool AcessoJogoCliente(SincControl &sincControl) {
		sincControl.hMutexJogo = OpenMutex(SYNCHRONIZE, FALSE, MUTEX_JOGO);
		sincControl.hEventoJogo = OpenEvent(FILE_MAP_WRITE, FALSE, EVENTO_JOGO);
		sincControl.hMemJogo = OpenFileMapping(FILE_MAP_READ, TRUE, SHM_JOGO);
		if (sincControl.hMutexJogo == NULL || sincControl.hEventoJogo == NULL || sincControl.hMemJogo == NULL) {
			_tprintf(TEXT("%s: [Erro: %d] Na criação de objectos (%s)...\n"), CLIENTE, GetLastError(), JOGO_TXT);
			return false;
		}
		sincControl.jogo = (JOGO*)MapViewOfFile(sincControl.hMemJogo, FILE_MAP_READ, 0, 0, sizeof(JOGO));
		if (sincControl.jogo == NULL) {
			_tprintf(TEXT("%s: [Erro: %d] No mapeamento da memória partilhada (%s)\n"), CLIENTE, GetLastError(), JOGO_TXT);
			return false;
		}
		return true;
	}
}