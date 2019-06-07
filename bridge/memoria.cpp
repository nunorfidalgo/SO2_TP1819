#include "bridge.h"

extern "C" {

	// Mensagens
	bool AcessoMensagensMemPartServidor(SincControl &sincControl) {
		sincControl.hMutexMensagem = CreateMutex(NULL, FALSE, MUTEX_MENSAGEM);
		sincControl.hEventoMensagem = CreateEvent(NULL, TRUE, FALSE, EVENTO_MENSAGEM);
		sincControl.hMemMensagem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(MENSAGEM), SHM_MENSAGEM);
		if (sincControl.hMemMensagem == NULL || sincControl.hMutexMensagem == NULL || sincControl.hEventoMensagem == NULL) {
			_tprintf(TEXT("%s: [Erro: %d] Na criação de objectos (%s)...\n"), SERVIDOR, GetLastError(), MENSAGEM_TXT);
			return false;
		}
		sincControl.mensagem = (MENSAGEM*)MapViewOfFile(sincControl.hMemMensagem, FILE_MAP_READ, 0, 0, sizeof(MENSAGEM));
		if (sincControl.mensagem == NULL) {
			_tprintf(TEXT("%s: [Erro: %d] No mapeamento da memória partilhada (%s)\n"), SERVIDOR, GetLastError(), MENSAGEM_TXT);
			return false;
		}
		return true;
	}

	bool AcessoMensagensMemPartCliente(SincControl &sincControl) {
		sincControl.hMutexMensagem = OpenMutex(SYNCHRONIZE, FALSE, MUTEX_MENSAGEM);
		sincControl.hEventoMensagem = OpenEvent(FILE_MAP_WRITE, FALSE, EVENTO_MENSAGEM);
		sincControl.hMemMensagem = OpenFileMapping(FILE_MAP_WRITE, TRUE, SHM_MENSAGEM);
		if (sincControl.hMutexMensagem == NULL || sincControl.hEventoMensagem == NULL || sincControl.hMemMensagem == NULL) {
			_tprintf(TEXT("%s: [Erro: %d] Na criação de objectos (%s)...\n"), CLIENTE, GetLastError(), MENSAGEM_TXT);
			return false;
		}
		sincControl.mensagem = (MENSAGEM*)MapViewOfFile(sincControl.hMemMensagem, FILE_MAP_WRITE, 0, 0, sizeof(MENSAGEM));
		if (sincControl.mensagem == NULL) {
			_tprintf(TEXT("%s: [Erro: %d] No mapeamento da memória partilhada (%s)\n"), CLIENTE, GetLastError(), MENSAGEM_TXT);
			return false;
		}
		return true;
	}

	// Jogo
	bool AcessoJogoMemPartServidor(SincControl &sincControl) {
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

	bool AcessoJogoMemPartCliente(SincControl &sincControl) {
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