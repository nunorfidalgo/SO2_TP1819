#ifndef FUNCS_H
#define FUNCS_H

bool verificaInstancia();
DWORD WINAPI threadRecebeMensagens(LPVOID param);
DWORD WINAPI threadEnviaJogo(LPVOID param);
DWORD WINAPI threadBola(LPVOID param);
DWORD WINAPI threadEscutaPipes(LPVOID param);

void MovimentoBola();

int escreveRegisto(TOPTEN& topten);
int leRegisto(TOPTEN& topten);
int apagaRegisto();

int leConfig(int argc, LPTSTR argv[]);
void mostraConfig(JOGO& jogo);

VOID instalaServico(void);
VOID __stdcall apagaServico();


#endif
