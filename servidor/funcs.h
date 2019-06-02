#ifndef FUNCS_H
#define FUNCS_H

bool verificaInstancia();
DWORD WINAPI threadRecebeMensagens(LPVOID param);
DWORD WINAPI threadEnviaJogo(LPVOID param);
DWORD WINAPI threadBola(LPVOID param);

void MovimentoBola();

//int escreveRegisto();
//int leRegisto();
int escreveRegisto(TOPTEN &topten);
int leRegisto(TOPTEN &topten);

#endif
