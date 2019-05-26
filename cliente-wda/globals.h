#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include "stdafx.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    NovoJogo(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    JogoConfigs(HWND, UINT, WPARAM, LPARAM);

JOGADOR jogador;
//BOLA bola;
SincControl sincControl;

TCHAR erros[MAX_LOADSTRING];

HANDLE hLogin;
HANDLE htTeclas, hTMensagens, hTJogo;
DWORD hTMensagensId, hTJogoId, htTeclasId;

#endif