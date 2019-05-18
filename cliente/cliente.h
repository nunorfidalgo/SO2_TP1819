#pragma once

#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>

#include "../bridge/bridge.h"

#include "cliente.h"

//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_NON_CONFORMING_SWPRINTFS
//#define UNICODE
//#define _UNICODE

#define TITLE_TEXT TEXT("Cliente Arkanoid/Breakout")

extern JOGADOR jogador;
extern SincControl sincControl;

extern HANDLE hLogin;
extern HANDLE htTeclas, hTMensagens, hTJogo;
extern DWORD hTMensagensId, hTJogoId, htTeclasId;

extern DWORD WINAPI envioMensagem(LPVOID param);
extern DWORD WINAPI recebeJogo(LPVOID param);
//DWORD WINAPI threadTeclas(LPVOID param);

extern LRESULT CALLBACK Cliente(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern INT_PTR CALLBACK JogoNovo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern INT_PTR CALLBACK JogoConfigs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
//LRESULT CALLBACK TrataEventos(HWND, UINT, WPARAM, LPARAM);