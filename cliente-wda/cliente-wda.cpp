// cliente-wda.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "cliente-wda.h"
#include "globals.h"
#include "funcs.h"

extern JOGADOR jogador;
extern SincControl sincControl;
extern TCHAR erros[MAX_LOADSTRING];

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	/**/

	if (!AcessoMensagensCliente(sincControl)) {
		MessageBox(NULL, TEXT("Erro ao aceder as mensagens"), MENSAGEM_TXT, MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	if (!AcessoJogoCliente(sincControl)) {
		MessageBox(NULL, TEXT("Erro ao aceder ao jogo"), JOGO_TXT, MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	hLogin = OpenEvent(FILE_MAP_WRITE, FALSE, LOGIN);
	if (hLogin == NULL) {
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [ERRO] Criação evento do login (%d)\n"), CLIENTE, GetLastError());
		MessageBox(NULL, erros, TEXT("Login"), MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_NOVO), NULL, NovoJogo);

	SetEvent(hLogin);
	ResetEvent(hLogin);
	CloseHandle(hLogin);

	hTMensagens = CreateThread(NULL, 0, threadEnvioMensagem, NULL, 0, &hTMensagensId);
	if (hTMensagens == NULL) {
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
		MessageBox(NULL, erros, TEXT("Thread Mensagens"), MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	hTJogo = CreateThread(NULL, 0, threadRecebeJogo, NULL, 0, &hTJogoId);
	if (hTJogo == NULL) {
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] Ao  criar a thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
		MessageBox(NULL, erros, TEXT("Thread Jogo"), MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	/*htTeclas = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTeclas, NULL, 0, &htTeclasId);
	if (htTeclas == NULL) {
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das teclas...\n"), CLIENTE, GetLastError(), htTeclasId);
		MessageBox(NULL, erros, TEXT("Thread Jogo"), MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}*/



	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENTEWDA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENTEWDA));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (WaitForSingleObject(hTMensagens, INFINITE) == NULL) {
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
		MessageBox(NULL, erros, TEXT("Thread Mensagens"), MB_ICONEXCLAMATION | MB_OK);
	}
	if ((WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
		MessageBox(NULL, erros, TEXT("Thread Jogo"), MB_ICONEXCLAMATION | MB_OK);
	}
	//if ((WaitForSingleObject(htTeclas, INFINITE)) == NULL) {
	//	_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das teclas...\n"), CLIENTE, GetLastError(), htTeclasId);
	//}

	closeSincControl(sincControl);
	CloseHandle(hTMensagens);
	CloseHandle(hTJogo);
	//CloseHandle(htTeclas);

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MENU));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MENU);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		_WINDOW_WIDTH,
		_WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
