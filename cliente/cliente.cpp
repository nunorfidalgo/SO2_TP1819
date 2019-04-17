#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"

#define SERVIDOR TEXT("Cliente:")

int _tmain(int argc, LPTSTR argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	_tprintf(TEXT("%s iniciou...\n"), SERVIDOR);
	AcedeMemoriaPartilhadaJogo();

	_tprintf(TEXT("%s teste de ção...\n"), SERVIDOR);

	return 0;
}
