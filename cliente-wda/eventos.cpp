#include "stdafx.h"
#include "cliente-wda.h"
#include "funcs.h"

extern HINSTANCE hInst;

extern JOGADOR jogador;
extern BOLA bola;
extern SincControl sincControl;
extern TCHAR erros[MAX_LOADSTRING];

HDC hdc = NULL;
HDC auxDC = NULL;
PAINTSTRUCT ps;
int sair;
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

		hBola = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BOLA), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		hBarreira = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BARREIRA), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);

		//hdc = GetDC(hWnd);
		GetObject(hBola, sizeof(bmBola), &bmBola);
		hdcBola = CreateCompatibleDC(hdc);
		SelectObject(hdcBola, hBola);
		//ReleaseDC(hWnd, hdc);

		//hdc = GetDC(hWnd);
		GetObject(hBarreira, sizeof(bmBarreira), &bmBarreira);
		hdcBarreira = CreateCompatibleDC(hdc);
		SelectObject(hdcBarreira, hBarreira);
		//ReleaseDC(hWnd, hdc);

		// Double Buffering
		hdc = GetDC(hWnd);
		auxDC = CreateCompatibleDC(hdc);
		auxBM = CreateCompatibleBitmap(hdc, _WINDOW_WIDTH, _WINDOW_HEIGHT);
		SelectObject(auxDC, auxBM);
		SelectObject(auxDC, /*bg*/CreateSolidBrush(RGB(255, 255, 255)));
		//PatBlt(auxDC, 0, 0, nX, nY, PATCOPY);
		PatBlt(auxDC, 0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT, PATCOPY);
		ReleaseDC(hWnd, hdc);

		// OBTEM AS DIMENSOES DO DISPLAY e define a cor de fundo;
		//bg = CreateSolidBrush(RGB(255, 255, 255)/*(8, 232, 222)*/);
		//nX = GetSystemMetrics(SM_CXSCREEN);
		//nY = GetSystemMetrics(SM_CYSCREEN);

	}
	break;

	case WM_PAINT:
	{
		// DESENHA NO 'DC' EM MEMORIA... 		
		//PatBlt(auxDC, 0, 0, nX, nY, PATCOPY);
		PatBlt(auxDC, 0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT, PATCOPY);

		/*BitBlt(auxDC, 180, 500, bmBola.bmWidth, bmBola.bmHeight, hdcBola, 0, 0, SRCCOPY);*/
		BitBlt(auxDC, bola.coord.x, bola.coord.y, bmBola.bmWidth, bmBola.bmHeight, hdcBola, 0, 0, SRCCOPY);

		//StretchBlt(auxDC, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, bmBola.bmWidth, bmBola.bmHeight, hdcBola, 0, 0, bmBola.bmWidth, bmBola.bmHeight, SRCCOPY);
		//TransparentBlt(auxDC, sincControl.jogo->bola.coord.x, sincControl.jogo->bola.coord.y, bmBola.bmWidth, bmBola.bmHeight, hdcBola, 0, 0, bmBola.bmWidth, bmBola.bmHeight, RGB(255, 255, 255));
		//InvalidateRect(hWnd, NULL, TRUE);

		//BitBlt(auxDC, 180, 520, bmBarreira.bmWidth, bmBarreira.bmHeight, hdcBarreira, 0, 0, SRCCOPY);X
		//BitBlt(auxDC, x, 520, bmBarreira.bmWidth, bmBarreira.bmHeight, hdcBarreira, 0, 0, SRCCOPY);
		BitBlt(auxDC, jogador.barreira.coord.x, 520, bmBarreira.bmWidth, bmBarreira.bmHeight, hdcBarreira, 0, 0, SRCCOPY);
		//StretchBlt(auxDC, jogador.barreira.coord.x, 520, 9, 90, hdcBarreira, 0, 0, 9, 90, SRCCOPY);
		//TransparentBlt(auxDC, jogador.barreira.coord.x, 520, 9, 90, hdcBarreira, 0, 0, 9, 90, RGB(255, 255, 255));
		//TransparentBlt(auxDC, jogador.barreira.coord.x, 520, 9, 90, hdcBarreira, 0, 0, 9, 90, RGB(255, 255, 255));
		//TransparentBlt(janelaAux, (pacoteTratar.dataPacket.arrayTab[i].x * escala), (pacoteTratar.dataPacket.arrayTab[i].y * escala), 40, 40, hdcDasImg.Basica, 0, 0, 40, 40, RGB(255, 255, 255)); // estica e tira a cor de fundo

		// COPIA INFORMACAO DO 'DC' EM MEMORIA PARA O DISPLAY... 
		hdc = BeginPaint(hWnd, &ps);
		//BitBlt(hdc, 0, 0, nX, nY, auxDC, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT, auxDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_MOUSEMOVE:
	{
		jogador.barreira.coord.x = GET_X_LPARAM(lParam);
		//GET_Y_LPARAM(lParam);

		InvalidateRect(hWnd, NULL, TRUE);
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
		InvalidateRect(hWnd, NULL, TRUE);
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