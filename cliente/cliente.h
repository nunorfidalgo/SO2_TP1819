#pragma once

#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include <locale.h>

#include "../bridge/bridge.h"
#include "cliente.h"

//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_NON_CONFORMING_SWPRINTFS
//#define UNICODE
//#define _UNICODE
//
//#ifdef _UNICODE
//#if defined _M_IX86
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#elif defined _M_IA64
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#elif defined _M_X64
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#else
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#endif
//#endif

#define TITLE_TEXT TEXT("Cliente Arkanoid/Breakout")

extern JOGADOR jogador;
extern SincControl sincControl;

extern HANDLE hLogin;
extern HANDLE htTeclas, hTMensagens, hTJogo;
extern DWORD hTMensagensId, hTJogoId, htTeclasId;

extern DWORD WINAPI envioMensagem(LPVOID param);
extern DWORD WINAPI recebeJogo(LPVOID param);
//DWORD WINAPI threadTeclas(LPVOID param);

LRESULT CALLBACK Cliente(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK JogoNovo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK JogoConfigs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
//LRESULT CALLBACK TrataEventos(HWND, UINT, WPARAM, LPARAM);