#include "stdafx.h"
#include "cliente-wda.h"

//#define TITLE_TEXT TEXT("Cliente Arkanoid/Breakout") -> definido nas string tables;
#define MAX_LOADSTRING 100

/* Global Variables */
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

JOGADOR jogador;
BOLA bola;
SincControl sincControl;
TCHAR erros[MAX_LOADSTRING];

HANDLE hLogin, hCliente;
HANDLE hTMensagens, hTJogo, htDoubleBuff;
DWORD hTMensagensId, hTJogoId, htDoubleBuffId;

HDC hDC = NULL, memDC = NULL, tempDC = NULL;
PAINTSTRUCT ps;
int sair = 0, maxX = 0, maxY = 0;
HBITMAP hBitMap = NULL, hBitBola = NULL, hBitBarreira = NULL;
BITMAP bmpBola, bmpBarreira;

HWND global_hWnd = NULL;


/* Funções */
bool verificaInstancia();
LRESULT CALLBACK trataEventos(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK NovoJogoLocal(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK NovoJogo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK JogoConfigs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

DWORD WINAPI threadEnvioMensagem(LPVOID param);
DWORD WINAPI threadRecebeJogo(LPVOID param);


/* WinMain */
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	if (verificaInstancia()) {
		PostQuitMessage(-1);
		return -1;
	}

	if (AcessoMensagensCliente(sincControl) && AcessoJogoCliente(sincControl)) {

		hLogin = OpenEvent(FILE_MAP_WRITE, FALSE, LOGIN);
		if (hLogin == NULL) {
			_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [ERRO] Criação evento do login (%d)\n"), CLIENTE, GetLastError());
			MessageBox(NULL, erros, TEXT("Login"), MB_ICONEXCLAMATION | MB_OK);
			return -1;
		}
		//MessageBox(NULL, TEXT("pipe"), TEXT("Thread Mensagens"), MB_ICONEXCLAMATION | MB_OK);
		DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_NOVO_LOCAL), NULL, NovoJogoLocal);
		SetEvent(hLogin);
		ResetEvent(hLogin);
		CloseHandle(hLogin);
	}
	else {
		//MessageBox(NULL, TEXT("Local"), TEXT("Thread Mensagens"), MB_ICONEXCLAMATION | MB_OK);
		DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_NOVO), NULL, NovoJogo);
		// name pipes...
	}

	//hLogin = OpenEvent(FILE_MAP_WRITE, FALSE, LOGIN);
	//if (hLogin == NULL) {
	//	/*_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [ERRO] Criação evento do login (%d)\n"), CLIENTE, GetLastError());
	//	MessageBox(NULL, erros, TEXT("Login"), MB_ICONEXCLAMATION | MB_OK);
	//	return -1;*/
	//	DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_NOVO), NULL, NovoJogo);
	//}
	//else {
	//	if (!AcessoMensagensCliente(sincControl)) {
	//		MessageBox(NULL, TEXT("Erro ao aceder as mensagens"), MENSAGEM_TXT, MB_ICONEXCLAMATION | MB_OK);
	//		return -1;
	//	}

	//	if (!AcessoJogoCliente(sincControl)) {
	//		MessageBox(NULL, TEXT("Erro ao aceder ao jogo"), JOGO_TXT, MB_ICONEXCLAMATION | MB_OK);
	//		return -1;
	//	}
	//	DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_NOVO_LOCAL), NULL, NovoJogoLocal);
	//}

	//SetEvent(hLogin);
	//ResetEvent(hLogin);
	//CloseHandle(hLogin);

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
		//_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
		//MessageBox(NULL, erros, TEXT("Thread Mensagens"), MB_ICONEXCLAMATION | MB_OK);
	}
	if ((WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
		//_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
		//MessageBox(NULL, erros, TEXT("Thread Jogo"), MB_ICONEXCLAMATION | MB_OK);
	}

	closeSincControl(sincControl);
	CloseHandle(hTMensagens);
	CloseHandle(hTJogo);

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
	wcex.lpfnWndProc = trataEventos;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MENU));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = /*CreateSolidBrush(RGB(8, 232, 222));*/ (HBRUSH)(COLOR_WINDOW + 1);
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

	global_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		/*CW_USEDEFAULT*/(GetSystemMetrics(SM_CXSCREEN) - _WINDOW_WIDTH) / 2,
		/*CW_USEDEFAULT*/(GetSystemMetrics(SM_CYSCREEN) - _WINDOW_HEIGHT) / 2,
		_WINDOW_WIDTH,
		_WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

	if (!global_hWnd)
	{
		return FALSE;
	}

	ShowWindow(global_hWnd, nCmdShow);
	UpdateWindow(global_hWnd);

	return TRUE;
}

DWORD WINAPI threadEnvioMensagem(LPVOID param) {
	jogador.barreira.coord.x = 180;
	enviaMensagem(sincControl, jogador);
	return 0;
}

DWORD WINAPI threadRecebeJogo(LPVOID param) {
	while (!sincControl.mensagem->termina) {
		//while (!sincControl.mensagem->termina || global_hWnd != NULL) {
		recebeJogo(sincControl, bola);
		//InvalidateRect(GetActiveWindow(), NULL, FALSE);
	}
	return 0;
}

INT_PTR CALLBACK NovoJogoLocal(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDC_EDIT_NOME));
		return (INT_PTR)FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT_NOME, sincControl.mensagem->jogador.nome, TEXTO);
			//_stprintf_s(erros, MAX_LOADSTRING, TEXT("nome jogador: %s"), sincControl.mensagem->jogador.nome);
			//MessageBox(NULL, erros, TEXT("Login"), MB_ICONEXCLAMATION | MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(-1);
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK NovoJogo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	SetFocus(GetDlgItem(hDlg, IDC_EDIT_NOME));
	switch (message)
	{
	case WM_INITDIALOG:
		//SetFocus(GetDlgItem(hDlg, IDC_EDIT_NOME));
		return (INT_PTR)FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			/*case IDC_EDIT_NOME:
				SetFocus(GetDlgItem(hDlg, IDC_EDIT_NOME));
				break;*/

		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT_NOME, sincControl.mensagem->jogador.nome, TEXTO);
			//GetDlgItemText(hDlg, IDC_IPADDRESS, sincControl.mensagem->jogador.???, TEXTO);
			//_stprintf_s(erros, MAX_LOADSTRING, TEXT("nome jogador: %s"), sincControl.mensagem->jogador.nome);
			//MessageBox(NULL, erros, TEXT("Login"), MB_ICONEXCLAMATION | MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(-1);
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK JogoConfigs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	SetFocus(GetDlgItem(hDlg, IDC_EDIT_ESQUERDA));
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


//HWND CreateSysLink(HWND hDlg, HINSTANCE hInst, RECT rect)
//{
//	return CreateWindowEx(0, WC_LINK,
//		L"For more information, <A HREF=\"https://www.microsoft.com\">click here</A> " \
//		L"or <A ID=\"idInfo\">here</A>.",
//		WS_VISIBLE | WS_CHILD | WS_TABSTOP,
//		rect.left, rect.top, rect.right, rect.bottom,
//		hDlg, NULL, hInst, NULL);
//}


//// Message handler for about box.
//INT_PTR CALLBACK trataDialogs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		switch (LOWORD(wParam)) {
//		case IDOK:
//			EndDialog(hDlg, 0);
//			return (INT_PTR)TRUE;
//			break;
//		case IDCANCEL:
//			/*MessageBox(NULL, TEXT("Teste"), TEXT("teste"), MB_ICONEXCLAMATION | MB_OK);*/
//			EndDialog(hDlg, 0);
//			return (INT_PTR)TRUE;
//			break;
//
//			// g_hLink is the handle of the SysLink control.
//		case WM_NOTIFY:
//
//			switch (((LPNMHDR)lParam)->code)
//			{
//
//			case NM_CLICK:          // Fall through to the next case.
//
//			case NM_RETURN:
//			{
//				MessageBox(NULL, TEXT("Teste SysLink"), TEXT("SysLink"), MB_ICONEXCLAMATION | MB_OK);
//				//PNMLINK pNMLink = (PNMLINK)lParam;
//				//LITEM   item = pNMLink->item;
//
//				//if (/*(((LPNMHDR)lParam)->hwndFrom == g_hLink) &&*/ (item.iLink == 0))
//				//{
//				//	ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);
//				//}
//
//				//else if (wcscmp(item.szID, L"idInfo") == 0)
//				//{
//				//	MessageBox(hDlg, L"This isn't much help.", L"Example", MB_OK);
//				//}
//
//				break;
//			}
//			}
//
//			break;
//			/*case IDC_SYSLINK1:
//				MessageBox(NULL, TEXT("Dialog Link"), TEXT("link"), MB_ICONEXCLAMATION | MB_OK);
//				EndDialog(hDlg, 0);
//				return (INT_PTR)TRUE;
//				break;*/
//				//case IDC_SYSLINK1:
//
//				//	switch (pNMHdr->code)
//				//	{
//				//	case NM_CLICK:
//				//	case NM_RETURN:
//				//	{
//				//		PNMLINK pNMLink = (PNMLINK)pNMHdr;
//				//		LITEM item = pNMLink->item;
//
//				//		// Judging by the index of the link 
//				//		if (item.iLink == 0) // If it is the first link 
//				//		{
//				//			ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);
//				//		}
//				//		// Judging by the ID of the link 
//				//		else if (wcscmp(item.szID, L"idBlog") == 0)
//				//		{
//				//			MessageBox(hDlg, L"http://blogs.msdn.com/codefx",
//				//				L"All-In-One Code Framework Blog", MB_OK);
//				//		}
//				//		break;
//				//	}
//				//	}
//
//				//	EndDialog(hDlg, 0);
//				//	return (INT_PTR)TRUE;
//				//	break;
//		}
//	}
//	return (INT_PTR)FALSE;
//}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK trataEventos(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // trataEventos
{
	switch (message)
	{

	case WM_COMMAND:
	{
		// Parse the menu selections:
		switch (LOWORD(wParam))
		{

		case IDM_SOBRE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SOBRE), hWnd, Sobre);
			break;

		case IDM_JOGO_NOVO:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_NOVO), hWnd, NovoJogo);
			break;

		case IDM_JOGO_CONFIGS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_CONFIG), hWnd, JogoConfigs);
			break;

		case IDM_JOGO_SAIR:
			sair = MessageBox(hWnd, TEXT("Sair do jogo?"), TEXT("Confirme:"), MB_YESNO);
			if (sair == IDYES) {
				//sincControl.mensagem->termina = 1;
				DestroyWindow(hWnd);
			}
			break;
		}
	}
	break;

	case WM_CREATE:
	{
		// Double Buffering
		maxX = GetSystemMetrics(SM_CXSCREEN);
		maxY = GetSystemMetrics(SM_CYSCREEN);

		hDC = BeginPaint(hWnd, &ps);
		memDC = CreateCompatibleDC(hDC);
		hBitMap = CreateCompatibleBitmap(hDC, maxX, maxY);
		SelectObject(memDC, hBitMap);
		DeleteObject(hBitMap);
		ReleaseDC(hWnd, hDC);

		hBitBola = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BOLA), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		GetObject(hBitBola, sizeof(bmpBola), &bmpBola);

		hBitBarreira = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BARREIRA), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		GetObject(hBitBarreira, sizeof(bmpBarreira), &bmpBarreira);

	}
	break;

	case WM_PAINT:
	{
		tempDC = CreateCompatibleDC(memDC);

		SelectObject(tempDC, hBitBarreira);
		PatBlt(memDC, 0, 0, maxX, maxY, PATCOPY);
		BitBlt(memDC, jogador.barreira.coord.x, 520, bmpBarreira.bmWidth, bmpBarreira.bmHeight, tempDC, 0, 0, SRCCOPY);

		SelectObject(tempDC, hBitBola);
		//PatBlt(memDC, 0, 0, maxX, maxY, PATCOPY);
		BitBlt(memDC, bola.coord.x, bola.coord.y, bmpBola.bmWidth, bmpBola.bmHeight, tempDC, 0, 0, SRCCOPY);

		DeleteDC(tempDC);

		hDC = BeginPaint(hWnd, &ps);
		BitBlt(hDC, 0, 0, maxX, maxY, memDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_MOUSEMOVE:
	{
		jogador.barreira.coord.x = GET_X_LPARAM(lParam);
		//GET_Y_LPARAM(lParam);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	//case WM_LBUTTONDOWN:
	//{
	//	RECT rect;
	//	int width, height;
	//	if (GetWindowRect(hWnd, &rect))
	//	{
	//		width = rect.right - rect.left;
	//		height = rect.bottom - rect.top;
	//	}
	//	_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: nX: %d, nY: %d\n"), CLIENTE, width, height);
	//	MessageBox(NULL, erros, TEXT("Info"), MB_ICONEXCLAMATION | MB_OK);
	//}
	//break;

	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_LEFT:
			jogador.barreira.coord.x -= 20;
			break;
		case VK_RIGHT:
			jogador.barreira.coord.x += 20;
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_CLOSE:
	{
		sair = MessageBox(hWnd, TEXT("Sair do jogo?"), TEXT("Confirme:"), MB_YESNO);
		if (sair == IDYES) {
			//sincControl.mensagem->termina = 1;
			DestroyWindow(hWnd);
		}
	}
	break;

	case WM_DESTROY:
	{
		sincControl.mensagem->termina = 1;

		DeleteObject(hBitBola);
		DeleteObject(hBitBarreira);

		DeleteObject(hBitMap);
		DeleteDC(memDC);

		DestroyWindow(hWnd);
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool verificaInstancia() {
	hCliente = CreateEventW(NULL, TRUE, FALSE, CLIENTE);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hCliente);
		hCliente = NULL;
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] Já exite uma instância do cliente a correr...\n"), CLIENTE, GetLastError());
		MessageBox(NULL, erros, CLIENTE, MB_ICONERROR | MB_OK);
		return true;
	}
	return false;
}