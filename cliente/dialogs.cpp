#include "cliente.h"
#include "resource.h"

HINSTANCE hInstDlg;

LRESULT CALLBACK Cliente(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int sair, x = 0, y = 0;

	switch (message) {
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_JOGO_NOVO:
			//MessageBox(NULL, TEXT("Menu Jogo Novo"), TEXT("confirmar"), MB_ICONEXCLAMATION | MB_OK);
			DialogBox(hInstDlg, MAKEINTRESOURCEW(IDD_JOGO_NOVO), hWnd, JogoNovo);
			break;
		case IDM_JOGO_CONFIGS:
			//MessageBox(NULL, TEXT("Menu Jogo Configs"), TEXT("confirmar"), MB_ICONEXCLAMATION | MB_OK);
			DialogBox(hInstDlg, MAKEINTRESOURCEW(IDD_JOGO_CONFIG), hWnd, JogoConfigs);
			break;
		case IDM_AJUDA_SOBRE:
			//MessageBox(NULL, TEXT("Menu Ajuda Sobre"), TEXT("confirmar"), MB_ICONEXCLAMATION | MB_OK);
			DialogBox(hInstDlg, MAKEINTRESOURCEW(IDD_AJUDA_SOBRE), hWnd, Sobre);
			break;
		case IDM_JOGO_SAIR:
			sair = MessageBox(hWnd, TEXT("Menu Jogo Sair?"), TEXT("Confirme:"), MB_YESNO);
			if (sair == IDYES)
				DestroyWindow(hWnd);
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_CLOSE:
		sair = MessageBox(hWnd, TEXT("Terminar cliente?"), TEXT("confirme:"), MB_YESNO);
		if (sair == IDYES)
			DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return(DefWindowProc(hWnd, message, wParam, lParam));
		break;
	}
	return(0);
}

INT_PTR CALLBACK JogoNovo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);

	switch (message) {
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			//case IDLIGAR:
			//	//GetDlgItemText(hDlg, IDC_EDIT1, login, 30);
			//	EndDialog(hDlg, 0);
			//	return (INT_PTR)TRUE;
			//	break;
			//case IDCANCELAR:
			//	EndDialog(hDlg, 0);
			//	return (INT_PTR)TRUE;
			//	break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK JogoConfigs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);

	switch (message) {
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);

	switch (message) {
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			/*case IDOK:
				EndDialog(hDlg, 0);
				return (INT_PTR)TRUE;
				break;*/
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
			//case IDLINK:
			//	MessageBox(NULL, TEXT("Dialog Link"), TEXT("link"), MB_ICONEXCLAMATION | MB_OK);
			//	//ShellExecute(hDlg, TEXT("open"), TEXT("https://github.com/nunorfidalgo/SO2-TP"), NULL, NULL, SW_SHOWDEFAULT);
			//	EndDialog(hDlg, 0);
			//	return (INT_PTR)TRUE;
			//	break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK TrataEventos(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;
	RECT rect;
	TCHAR text_clicks[20];

	switch (messg) {
	case WM_RBUTTONDOWN:

		/*_stprintf_s(text_clicks, 20, TEXT("Num. de Clicks = 1"));*/
		hdc = GetDC(hWnd);
		GetClientRect(hWnd, &rect);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);
		rect.left += 5;
		rect.top += 5;
		DrawText(hdc, text_clicks, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
		ReleaseDC(hWnd, hdc);

		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("Are you sure?"), TEXT("Quit Application"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
			DestroyWindow(hWnd);
		}
		break;

	case WM_DESTROY: // Destruir a janela e terminar o programa
		// "PostQuitMessage(Exit Status)"
		PostQuitMessage(0);
		break;
	default:
		// Neste exemplo, para qualquer outra mensagem (p.e. "minimizar","maximizar","restaurar")
		// não é efectuado nenhum processamento, apenas se segue o "default" do Windows
		return DefWindowProc(hWnd, messg, wParam, lParam);
		break;
	}
	return(0);
}

//DWORD WINAPI threadTeclas(LPVOID param) {
	// barreira do jogador, posição inicial da barreira e posição anterior
	//jogador.barreira.coord.x = 1;
	//jogador.barreira.coord.y = LINHAS;
	//TCHAR key_input;
	//while (!sincControl.mensagem->termina) {
	//	key_input = _gettch();
	//	key_input = toupper(key_input);
	//	_flushall();
	//	switch (key_input) {
	//	case 77: //direta
	//		if (jogador.barreira.coord.x < COLUNAS - 5) {
	//			jogador.barreira.coord.x += 5;
	//		}
	//		break;
	//	case 75: // esquerda
	//		if (jogador.barreira.coord.x > 1) {
	//			jogador.barreira.coord.x -= 5;
	//		}
	//		break;
	//	case 27: // ESC = sair
	//		sincControl.mensagem->termina = 1;
	//		WaitForSingleObject(sincControl.hMutexJogo, INFINITE);
	//		gotoxy(0, LINHAS + 2);
	//		_tprintf(TEXT("Jogador cancelou do jogo...\n"));
	//		ReleaseMutex(sincControl.hMutexJogo);
	//		return -1;
	//		break;
	//	}
	//}
//	return 0;
//}