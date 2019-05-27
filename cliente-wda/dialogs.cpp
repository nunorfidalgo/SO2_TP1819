#include "stdafx.h"
#include "Resource.h"
#include "funcs.h"

extern HINSTANCE hInst;
extern SincControl sincControl;
extern TCHAR erros[MAX_LOADSTRING];

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

INT_PTR CALLBACK NovoJogoLocal(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

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
			break;
		}
		//if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		//{
		//	GetDlgItemText(hDlg, IDC_EDIT_NOME, sincControl.mensagem->jogador.nome, TEXTO);
		//	EndDialog(hDlg, LOWORD(wParam));
		//	return (INT_PTR)TRUE;
		//}


		break;
	}
	return (INT_PTR)FALSE;
}

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