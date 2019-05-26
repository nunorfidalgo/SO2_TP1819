#pragma once
#include "stdafx.h"

#ifndef FUNCS_H
#define FUNCS_H

LRESULT CALLBACK trataEventos(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK trataDialogs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK NovoJogoLocal(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK NovoJogo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK JogoConfigs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


DWORD WINAPI threadEnvioMensagem(LPVOID param);
DWORD WINAPI threadRecebeJogo(LPVOID param);
//DWORD WINAPI threadTeclas(LPVOID param);

#endif