#include "stdafx.h"
#include "cliente-wda.h"
#include "funcs.h"

extern HINSTANCE hInst;

extern JOGADOR jogador;
extern BOLA bola;
extern SincControl sincControl;
extern TCHAR erros[MAX_LOADSTRING];

HDC hDC = NULL, memDC = NULL, tempDC = NULL;
PAINTSTRUCT ps;
int sair = 0, maxX = 0, maxY = 0;
HBITMAP hBitMap = NULL, hBitBola = NULL, hBitBarreira = NULL;
BITMAP bmpBola, bmpBarreira;

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
				sincControl.mensagem->termina = 1;
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

		memDC = GetDC(hWnd);
		memDC = CreateCompatibleDC(memDC);
		hBitMap = CreateCompatibleBitmap(memDC, maxX, maxY);
		SelectObject(memDC, hBitMap);
		PatBlt(memDC, 0, 0, maxX, maxY, PATCOPY);
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
		DeleteDC(tempDC);

		/*SelectObject(tempDC, hBitBola);
		PatBlt(auxDC, 0, 0, maxX, maxY, PATCOPY);
		BitBlt(auxDC, bola.coord.x, bola.coord.y, bmpBola.bmWidth, bmpBola.bmHeight, tempDC, 0, 0, SRCCOPY);*/

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
			jogador.barreira.coord.x -= 5;
			break;
		case VK_RIGHT:
			jogador.barreira.coord.x += 5;
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_CLOSE:
	{
		sair = MessageBox(hWnd, TEXT("Sair do jogo?"), TEXT("Confirme:"), MB_YESNO);
		if (sair == IDYES)
			DestroyWindow(hWnd);
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