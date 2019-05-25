#pragma once
#ifndef FUNCS_H
#define FUNCS_H

void entrar();
void imprimeJogo();
void teclas();

DWORD WINAPI threadEnvioMensagem(LPVOID param);
DWORD WINAPI threadRecebeJogo(LPVOID param);
DWORD WINAPI threadTeclas(LPVOID param);

#endif