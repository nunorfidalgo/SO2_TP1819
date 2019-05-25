#include "stdafx.h"
#include "Resource.h"
#include "funcs.h"

extern HINSTANCE hInst;

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // trataEventos
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_SOBRE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SOBRE), hWnd, About);
			break;
		case IDM_JOGO_NOVO:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_NOVO), hWnd, NovoJogo);
			break;
		case IDM_JOGO_CONFIGS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_JOGO_CONFIG), hWnd, JogoConfigs);
			break;
		case IDM_JOGO_SAIR:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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

// Message handler for about box.
INT_PTR CALLBACK trataDialogs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
		case IDCANCEL:
			/*MessageBox(NULL, TEXT("Teste"), TEXT("teste"), MB_ICONEXCLAMATION | MB_OK);*/
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;

			// g_hLink is the handle of the SysLink control.
		case WM_NOTIFY:

			switch (((LPNMHDR)lParam)->code)
			{

			case NM_CLICK:          // Fall through to the next case.

			case NM_RETURN:
			{
				MessageBox(NULL, TEXT("Teste SysLink"), TEXT("SysLink"), MB_ICONEXCLAMATION | MB_OK);
				//PNMLINK pNMLink = (PNMLINK)lParam;
				//LITEM   item = pNMLink->item;

				//if (/*(((LPNMHDR)lParam)->hwndFrom == g_hLink) &&*/ (item.iLink == 0))
				//{
				//	ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);
				//}

				//else if (wcscmp(item.szID, L"idInfo") == 0)
				//{
				//	MessageBox(hDlg, L"This isn't much help.", L"Example", MB_OK);
				//}

				break;
			}
			}

			break;
			/*case IDC_SYSLINK1:
				MessageBox(NULL, TEXT("Dialog Link"), TEXT("link"), MB_ICONEXCLAMATION | MB_OK);
				EndDialog(hDlg, 0);
				return (INT_PTR)TRUE;
				break;*/
				//case IDC_SYSLINK1:

				//	switch (pNMHdr->code)
				//	{
				//	case NM_CLICK:
				//	case NM_RETURN:
				//	{
				//		PNMLINK pNMLink = (PNMLINK)pNMHdr;
				//		LITEM item = pNMLink->item;

				//		// Judging by the index of the link 
				//		if (item.iLink == 0) // If it is the first link 
				//		{
				//			ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);
				//		}
				//		// Judging by the ID of the link 
				//		else if (wcscmp(item.szID, L"idBlog") == 0)
				//		{
				//			MessageBox(hDlg, L"http://blogs.msdn.com/codefx",
				//				L"All-In-One Code Framework Blog", MB_OK);
				//		}
				//		break;
				//	}
				//	}

				//	EndDialog(hDlg, 0);
				//	return (INT_PTR)TRUE;
				//	break;
		}
	}
	return (INT_PTR)FALSE;
}

// Message handler for about box.
INT_PTR CALLBACK NovoJogo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

// Message handler for about box.
INT_PTR CALLBACK JogoConfigs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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