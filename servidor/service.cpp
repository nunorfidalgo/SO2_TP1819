//
// Purpose: 
//   Installs a service in the SCM database
//
// Parameters:
//   None
// 
// Return value:
//   None
//

#pragma comment(lib, "advapi32.lib")

#include "servidor.h"

#define SVCNAME TEXT("SO2Servidor")


//#define MAX_PATH 256

VOID instalaServico() {
	SC_HANDLE schSCManager;
	SC_HANDLE schService;

	TCHAR szPath[MAX_PATH] = TEXT("D:\\CloudFiles\\GitHub\\SO2_TP1819\\Debug\\servidor.exe");
	//TCHAR szPath[MAX_PATH] = TEXT("c:\\servidor.exe");

	HINSTANCE hInstance = GetModuleHandle(NULL);

	//GetModuleFileNameA(hInstance, FileName, sizeof(FileName));

	//if (!GetModuleFileNameW(TEXT( "" ), szPath, MAX_PATH)) {
	if (!GetModuleFileNameW(hInstance, szPath, sizeof(TCHAR))) {
		_tprintf(TEXT("Sem permissões para instalar serviço... (%d)\n"), GetLastError());
		return;
	}

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		//SC_MANAGER_ALL_ACCESS);  // full access rights 
		GENERIC_ALL);

	if (NULL == schSCManager) {
		_tprintf(TEXT("Sem permissões para aceder ao gestor de serviços... (%d)\n"), GetLastError());
		return;
	}

	// Create the service

	schService = CreateService(
		schSCManager,              // SCM database 
		SVCNAME,                   // name of service 
		SVCNAME,                   // service name to display 
		SERVICE_ALL_ACCESS,        // desired access 
		//STANDARD_RIGHTS_EXECUTE,
		SERVICE_WIN32_OWN_PROCESS, // service type 
		SERVICE_AUTO_START,      // start type 
		SERVICE_ERROR_NORMAL,      // error control type 
		TEXT("D:\\CloudFiles\\GitHub\\SO2_TP1819\\Debug\\servidor.exe"),// path to service's binary 
		NULL,                      // no load ordering group 
		NULL,                      // no tag identifier 
		NULL,                      // no dependencies
		//TEXT("NT AUTHORITY\\NetworkService"),
		NULL,                      // LocalSystem account 
		NULL);                     // no password 

	if (schService == NULL) {
		_tprintf(TEXT("Falha ao instalar serviço (%d)...\n"), GetLastError());
		CloseServiceHandle(schSCManager);
		return;
	}
	else _tprintf(TEXT("Serviço instalado com sucesso...\n"));

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}

VOID __stdcall apagaServico() {
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	//SERVICE_STATUS ssStatus;

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager) {
		_tprintf(TEXT("Sem permissões para aceder ao gestor de serviços... (%d)\n"), GetLastError());
		return;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,       // SCM database 
		TEXT("SO2Servidor"),      // name of service 
		DELETE);            // need delete access 

	if (schService == NULL) {
		_tprintf(TEXT("Serviço não existe...(%d)\n"), GetLastError());
		CloseServiceHandle(schSCManager);
		return;
	}

	// Delete the service.

	if (!DeleteService(schService)) {
		_tprintf(TEXT("Falha ao apagar serviço... (%d)\n"), GetLastError());
	}
	else
		_tprintf(TEXT("Serviço apagado...\n"));

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}