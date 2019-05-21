#include "cliente.h"
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {

	//setlocale(LC_ALL, "pt-PT");

	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcApp;
	wcApp.cbSize = sizeof(WNDCLASSEX);
	wcApp.hInstance = hInst;
	wcApp.lpszClassName = CLIENTE;
	wcApp.lpfnWndProc = Cliente; // TrataEventos;
	wcApp.style = CS_HREDRAW | CS_VREDRAW;
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcApp.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcApp.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU);
	wcApp.cbClsExtra = 0;
	wcApp.cbWndExtra = 0;
	wcApp.hbrBackground = CreateSolidBrush(RGB(0, 0, 180));

	if (!RegisterClassEx(&wcApp))
		return(0);

	hWnd = CreateWindow(
		CLIENTE,
		TITLE_TEXT,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		450,
		600,
		(HWND)HWND_DESKTOP,
		(HMENU)NULL,
		(HINSTANCE)hInst,
		0);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/*if (!AcessoMensagensCliente(sincControl)) {
		return -1;
	}

	if (!AcessoJogoCliente(sincControl)) {
		return -1;
	}*/

	/*hLogin = OpenEvent(FILE_MAP_WRITE, FALSE, TEXT("LOGIN"));
	if (hLogin == NULL) {
		_tprintf(TEXT("%s: [ERRO] Criação evento do login (%d)\n"), CLIENTE, GetLastError());
		exit(-1);
	}

	SetEvent(hLogin);
	ResetEvent(hLogin);
	CloseHandle(hLogin);*/

	/*hTMensagens = CreateThread(NULL, 0, envioMensagem, NULL, 0, &hTMensagensId);
	if (hTMensagens == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
		return -1;
	}

	hTJogo = CreateThread(NULL, 0, recebeJogo, NULL, 0, &hTJogoId);
	if (hTJogo == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
		return -1;
	}

	htTeclas = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadTeclas, NULL, 0, &htTeclasId);
	if (htTeclas == NULL) {
		_tprintf(TEXT("%s: [Erro: %d] Ao  criar a thread[%d] das teclas...\n"), CLIENTE, GetLastError(), htTeclasId);
		return -1;
	}*/

	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg); // Pré-processamento da mensagem (p.e. obter código
		DispatchMessage(&lpMsg); // Enviar a mensagem traduzida de volta ao Windows, que
	}


	//if (WaitForSingleObject(hTMensagens, INFINITE) == NULL) {
	//	_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das mensagens...\n"), CLIENTE, GetLastError(), hTMensagensId);
	//	//return -1;
	//}
	//if ((WaitForSingleObject(hTJogo, INFINITE)) == NULL) {
	//	_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] do jogo...\n"), CLIENTE, GetLastError(), hTJogoId);
	//	//return -1;
	//}
	//if ((WaitForSingleObject(htTeclas, INFINITE)) == NULL) {
	//	_tprintf(TEXT("%s: [Erro: %d] WaitForSingleObject da thread[%d] das teclas...\n"), CLIENTE, GetLastError(), htTeclasId);
	//	//return -1;
	//}

	//closeSincControl(sincControl);
	//CloseHandle(hTMensagens);
	//CloseHandle(hTJogo);
	//CloseHandle(htTeclas);

	return((int)lpMsg.wParam); // Retorna sempre o parâmetro wParam da estrutura lpMsg
}