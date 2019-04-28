#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "dados.h"
#include "../bridge/bridge.h"

TCHAR NomeMemoria[] = TEXT("teste");
HANDLE hMutex;
HANDLE hEvento;
HANDLE hMemoria;


int _tmain(int argc, LPTSTR argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	HANDLE PacoteSrv, hMapMemSrv;
	system("cls");
	_tprintf(TEXT("%s iniciou...\n"), SERVIDOR);
	//CriaMemoriaPartilhadaJogo();
	/*PacoteSrv = CriaMemPartCom(hMapMemSrv);

	_gettchar();*/


	Pacote *pacote;
	//char init = 1;


	system("cls");
	// criar mutex
	hMutex = CreateMutex(NULL, FALSE, TEXT("Mutex"));
	// Criar MUTEX
	// mutex
	//hMutex = CreateMutex(NULL, TRUE, TEXT("MutexIn"));
	//if (MutexIn == NULL) {
	//	_tprintf(TEXT("CreateMutex error: %d\n"), GetLastError());
	//	return 1;
	//}

	hEvento = CreateEvent(NULL, TRUE, FALSE, TEXT("Evento"));

	hMemoria = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(Pacote), NomeMemoria);
	if (hMutex == NULL || hEvento == NULL || hMemoria == NULL) {
		_tprintf(TEXT("[Erro]Criação de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	pacote = (Pacote*)MapViewOfFile(hMemoria, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Pacote));
	if (pacote == NULL) {
		_tprintf(TEXT("[Erro]Mapeamento da memória partilhada(%d)\n"), GetLastError());
		return -1;
	}

	while (1)
	{
		WaitForSingleObject(hEvento, INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		_tprintf(TEXT("Jogador (%d,%d): %s  | Bola=(%d,%d) \n"), pacote->jogadorx, pacote->jogadory, pacote->nome, pacote->bolax, pacote->bolay);

		/*_tprintf(TEXT("pacote->nome: %s\n"), pacote->nome);
		_tprintf(TEXT("pacote->bolax: %d\n"), pacote->bolax);
		_tprintf(TEXT("pacote->bolay: %d\n"), pacote->bolay);
		_tprintf(TEXT("pacote->jogadorx: %d\n"), pacote->jogadorx);
		_tprintf(TEXT("pacote->jogadory: %d\n"), pacote->jogadory);
		_tprintf(TEXT("************************************\n"));*/
		// libertar o mutex
		ReleaseMutex(hMutex);
	}

	UnmapViewOfFile(pacote);

	CloseHandle(hMutex);
	CloseHandle(hEvento);
	CloseHandle(hMemoria);

	return 0;
}
