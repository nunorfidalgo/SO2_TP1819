#include "stdafx.h"
#include "cliente-wda.h"

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

HANDLE hLogin, hCliente, hTJogo;
DWORD hTJogoId;

HDC hDC = NULL, memDC = NULL, tempDC = NULL;
PAINTSTRUCT ps;
int sair = 0, maxX = 0, maxY = 0;
HBITMAP hBitMap = NULL, hBitBola = NULL, hBitBarreira = NULL;
BITMAP bmpBola, bmpBarreira;

RECT rect;
HWND global_hWnd = NULL;

HANDLE hPipe;

bool local;

MENSAGEM mensagem;

/* Fun��es */
bool verificaInstancia();
LRESULT CALLBACK trataEventos(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK NovoJogoLocal(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK NovoJogo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK JogoConfigs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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

	jogador.barreira.coord.x = 180; // posi��o inicial
	jogador.barreira.coord.y = 0;
	jogador.cor = 0;
	jogador.pontos = 0;
	_tcscpy_s(jogador.nome, TEXT(""));

	memcpy(&jogador, &mensagem.jogador, sizeof(JOGADOR));
	mensagem.termina = 0;

	if (verificaInstancia()) {
		PostQuitMessage(-1);
		return -1;
	}

	//if (AcessoMensagensMemPartCliente(sincControl) && AcessoJogoMemPartCliente(sincControl)) {

		/*hLogin = OpenEvent(FILE_MAP_WRITE, FALSE, LOGIN);
		if (hLogin == NULL) {
			_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [ERRO] Cria��o evento do login (%d)\n"), CLIENTE, GetLastError());
			MessageBox(NULL, erros, TEXT("Login"), MB_ICONEXCLAMATION | MB_OK);
			return -1;
		}*/
		//MessageBox(NULL, TEXT("pipe"), TEXT("Thread Mensagens"), MB_ICONEXCLAMATION | MB_OK);
	//DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_NOVO_LOCAL), NULL, NovoJogoLocal);
	/*SetEvent(hLogin);
	ResetEvent(hLogin);
	CloseHandle(hLogin);*/
	//	local = true;
	//}
	//else {
		//MessageBox(NULL, TEXT("Local"), TEXT("Thread Mensagens"), MB_ICONEXCLAMATION | MB_OK);

	// named pipes
	if (!AcessoPipeMensagensCliente(hPipe)) {
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("[ERRO] Ligar ao pipe '%s'! (CreateFile)\n"), PIPE_NAME);
		MessageBox(NULL, erros, TEXT("Pipe"), MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}
	/*DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_NOVO), NULL, NovoJogo);*/

	_tcscpy_s(jogador.nome, TEXT("dasdasdasd"));
	_tcscpy_s(mensagem.jogador.nome, jogador.nome);

	_stprintf_s(erros, MAX_LOADSTRING, TEXT("Nome: %s\n"), mensagem.jogador.nome);
	MessageBox(NULL, erros, TEXT("Pipe"), MB_ICONEXCLAMATION | MB_OK);

	enviaMensagemPipe(hPipe, &mensagem);
	local = false;

	//}

	//enviaMensagem(sincControl, jogador);

	/*hTMensagens = CreateThread(NULL, 0, threadEnvioMensagem, NULL, 0, &hTMensagensId);
	if (hTMensagens == NULL) {
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
		MessageBox(NULL, erros, TEXT("Thread Mensagens"), MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}*/

	//hTJogo = CreateThread(NULL, 0, threadRecebeJogo, NULL, 0, &hTJogoId);
	//if (hTJogo == NULL) {
	//	_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] Ao  criar a thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
	//	MessageBox(NULL, erros, TEXT("Thread Jogo"), MB_ICONEXCLAMATION | MB_OK);
	//	return -1;
	//}

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
	WaitForSingleObject(hTJogo, INFINITE);

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
		(GetSystemMetrics(SM_CXSCREEN) - _WINDOW_WIDTH) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - _WINDOW_HEIGHT) / 2,
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

DWORD WINAPI threadRecebeJogo(LPVOID param) {
	while (!sincControl.mensagem->termina || !mensagem.termina) {

		recebeJogoMemPart(sincControl, bola);
		tempDC = CreateCompatibleDC(memDC);

		SelectObject(tempDC, hBitBarreira);
		PatBlt(memDC, 0, 0, maxX, maxY, PATCOPY);
		BitBlt(memDC, jogador.barreira.coord.x, 520, bmpBarreira.bmWidth, bmpBarreira.bmHeight, tempDC, 0, 0, SRCCOPY);

		SelectObject(tempDC, hBitBola);
		BitBlt(memDC, bola.coord.x, bola.coord.y, bmpBola.bmWidth, bmpBola.bmHeight, tempDC, 0, 0, SRCCOPY);

		DeleteDC(tempDC);
		InvalidateRect(global_hWnd, NULL, TRUE);
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
			GetDlgItemText(hDlg, IDC_EDIT_NOME, jogador.nome, TEXTO);
			enviaMensagemMemPart(sincControl, jogador);
			EndDialog(hDlg, LOWORD(wParam));
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			DestroyWindow(global_hWnd);
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
		return (INT_PTR)FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			/*GetDlgItemText(hDlg, IDC_EDIT_NOME, jogador.nome, TEXTO);
			_tcscpy_s(mensagem.jogador.nome, jogador.nome);
			enviaMensagemPipe(hPipe, &mensagem);*/
			EndDialog(hDlg, LOWORD(wParam));
			/*MessageBox(hDlg, TEXT("Falta implementar"), TEXT("ERRO"), MB_ICONERROR | MB_OK);
			DestroyWindow(global_hWnd);
			PostQuitMessage(-1);*/
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			DestroyWindow(global_hWnd);
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
		hDC = BeginPaint(hWnd, &ps);
		BitBlt(hDC, 0, 0, maxX, maxY, memDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_ERASEBKGND:
		return (1);
		break;

	case WM_MOUSEMOVE:
	{
		GetClientRect(hWnd, &rect); // dimens�o da janela...
		jogador.barreira.coord.x = GET_X_LPARAM(lParam);
		if (jogador.barreira.coord.x < 0)
			jogador.barreira.coord.x = 0;
		if (jogador.barreira.coord.x > (unsigned int)(rect.right - bmpBarreira.bmWidth))
			jogador.barreira.coord.x = rect.right - bmpBarreira.bmWidth;
		if (local == true)
			enviaMensagemMemPart(sincControl, jogador);
		else {
			enviaMensagemPipe(hPipe, &mensagem);
		}
	}
	break;

	case WM_KEYDOWN:
	{
		GetClientRect(hWnd, &rect); // dimens�o da janela...
		switch (wParam) {
		case VK_LEFT:
			jogador.barreira.coord.x = jogador.barreira.coord.x > 0 ? jogador.barreira.coord.x - 20 : 0;
			break;
		case VK_RIGHT:
			jogador.barreira.coord.x = jogador.barreira.coord.x < (unsigned int)(rect.right - bmpBarreira.bmWidth) ? jogador.barreira.coord.x + 20 : (unsigned int)(rect.right - bmpBarreira.bmWidth);
			break;
		}
		if (local == true)
			enviaMensagemMemPart(sincControl, jogador);
		else {
			enviaMensagemPipe(hPipe, &mensagem);
		}
	}
	break;

	case WM_CLOSE:
	{
		sair = MessageBox(hWnd, TEXT("Sair do jogo?"), TEXT("Confirme:"), MB_YESNO);
		if (sair == IDYES) {
			DestroyWindow(hWnd);
		}
	}
	break;

	case WM_DESTROY:
	{
		sincControl.mensagem->termina = 1;
		mensagem.termina = 1;
		if (local == true)
			enviaMensagemMemPart(sincControl, jogador);
		else {
			enviaMensagemPipe(hPipe, &mensagem);
		}

		DeleteObject(hBitBola);
		DeleteObject(hBitBarreira);

		DeleteObject(hBitMap);
		DeleteDC(memDC);

		closeSincControl(sincControl);
		CloseHandle(hPipe);
		CloseHandle(hTJogo);

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
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: [Erro: %d] J� exite uma inst�ncia do cliente a correr...\n"), CLIENTE, GetLastError());
		MessageBox(NULL, erros, CLIENTE, MB_ICONERROR | MB_OK);
		return true;
	}
	return false;
}