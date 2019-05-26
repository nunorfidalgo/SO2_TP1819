#include "stdafx.h"
#include "Resource.h"
#include "funcs.h"

#define MAX_LOADSTRING 100

extern HINSTANCE hInst;
extern JOGADOR jogador;
//extern BOLA bola;
extern SincControl sincControl;
extern TCHAR erros[MAX_LOADSTRING];

HDC hdc = NULL;
HDC auxDC = NULL;
PAINTSTRUCT ps;

int sair, nX = 0, nY = 0;
// bola posicão inicial 180, 500

HBRUSH bg = NULL;
HBITMAP auxBM = NULL;
HBITMAP hBola, hBarreira;
BITMAP bmBola, bmBarreira;
HDC hdcBola, hdcBarreira;

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
		hdc = GetDC(hWnd);

		hBola = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BOLA), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		GetObject(hBola, sizeof(bmBola), &bmBola);
		hdcBola = CreateCompatibleDC(hdc);
		SelectObject(hdcBola, hBola);

		hBarreira = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BARREIRA), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		GetObject(hBarreira, sizeof(bmBarreira), &bmBarreira);
		hdcBarreira = CreateCompatibleDC(hdc);
		SelectObject(hdcBarreira, hBarreira);

		// OBTEM AS DIMENSOES DO DISPLAY e define a cor de fundo;
		bg = CreateSolidBrush(RGB(255, 255, 255)/*(8, 232, 222)*/);
		nX = GetSystemMetrics(SM_CXSCREEN);
		nY = GetSystemMetrics(SM_CYSCREEN);

		// PREPARA 'BITMAP' E ASSOCIA A UM 'DC' EM MEMORIA... 
		auxDC = CreateCompatibleDC(hdc);
		auxBM = CreateCompatibleBitmap(hdc, nX, nY);
		SelectObject(auxDC, auxBM);
		SelectObject(auxDC, bg);
		PatBlt(auxDC, 0, 0, nX, nY, PATCOPY);

		ReleaseDC(hWnd, hdc);
	}
	break;

	case WM_PAINT:
	{
		// DESENHA NO 'DC' EM MEMORIA... 		
		PatBlt(auxDC, 0, 0, nX, nY, PATCOPY);

		BitBlt(auxDC, 180, 500, bmBola.bmWidth, bmBola.bmHeight, hdcBola, 0, 0, SRCCOPY);
		//BitBlt(auxDC, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, bmBola.bmWidth, bmBola.bmHeight, hdcBola, 0, 0, SRCCOPY);
		//BitBlt(auxDC, 180, 520, bmBarreira.bmWidth, bmBarreira.bmHeight, hdcBarreira, 0, 0, SRCCOPY);
		//BitBlt(auxDC, x, 520, bmBarreira.bmWidth, bmBarreira.bmHeight, hdcBarreira, 0, 0, SRCCOPY);
		BitBlt(auxDC, jogador.barreira.coord.x, 520, bmBarreira.bmWidth, bmBarreira.bmHeight, hdcBarreira, 0, 0, SRCCOPY);

		// COPIA INFORMACAO DO 'DC' EM MEMORIA PARA O DISPLAY... 
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, nX, nY, auxDC, 0, 0, SRCCOPY);
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

	case WM_LBUTTONDOWN:
	{
		RECT rect;
		int width, height;
		if (GetWindowRect(hWnd, &rect))
		{
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}
		_stprintf_s(erros, MAX_LOADSTRING, TEXT("%s: nX: %d, nY: %d\n"), CLIENTE, width, height);
		MessageBox(NULL, erros, TEXT("Info"), MB_ICONEXCLAMATION | MB_OK);
	}
	break;

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

		DeleteObject(hBola);
		DeleteDC(hdcBola);

		DeleteObject(hBarreira);
		DeleteDC(hdcBarreira);

		DeleteObject(bg);
		DeleteObject(auxBM);
		DeleteDC(auxDC);

		DestroyWindow(hWnd);
		PostQuitMessage(0);

	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
