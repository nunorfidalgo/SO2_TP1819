#include "bridge.h"

BRIDGE_API BOOL APIENTRY WINAPI DllMain(HANDLE hInstance, DWORD fdwReason, LPVOID lpvReserved) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("Bridge (DDL): Ocorreu um erro ao iniciar a DLL!\n"));
		else
			_tprintf(TEXT("Bridge (DDL): pronta...\n"));
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("Bridge (DDL): Ocorreu um erro a terminar a DLL!\n"));
		else
			_tprintf(TEXT("Brige (DDL): terminou..."));
		break;
	}
	return 1;
}