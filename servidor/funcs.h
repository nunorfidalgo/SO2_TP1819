#ifndef FUNCS_H
#define FUNCS_H

bool verificaInstancia();
DWORD WINAPI threadRecebeMensagens(LPVOID param);
DWORD WINAPI threadEnviaJogo(LPVOID param);
DWORD WINAPI threadBola(LPVOID param);
DWORD WINAPI threadEscutaPipes(LPVOID param);

void MovimentoBola();

//int escreveRegisto();
//int leRegisto();
int escreveRegisto(TOPTEN& topten);
int leRegisto(TOPTEN& topten);

int leConfig(int argc, LPTSTR argv[]);
void mostraConfig(JOGO& jogo);

#endif
