#include "bridge.h"
#include "sinc.h"
#include "mensagem.h"

extern "C" {

	bool AcessoMensagensServidor(SincControl &sincControl) {
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

	bool AcessoMensagensCliente(SincControl &sincControl) {
		//sincControl.hMutexMensagem = CreateMutex(NULL, FALSE, MUTEX_MENSAGEM);
		//sincControl.hEventoMensagem = CreateEvent(NULL, TRUE, FALSE, EVENTO_MENSAGEM);
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

}