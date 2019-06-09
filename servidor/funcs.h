#ifndef FUNCS_H
#define FUNCS_H

bool verificaInstancia();
DWORD WINAPI threadRecebeMensagens(LPVOID param);
DWORD WINAPI threadEnviaJogo(LPVOID param);
DWORD WINAPI threadBola(LPVOID param);

void MovimentoBola();

int escreveRegisto(TOPTEN& topten);
int leRegisto(TOPTEN& topten);
int apagaRegisto();

int leConfig(int argc, LPTSTR argv[]);
void mostraConfig(JOGO& jogo);

VOID instalaServico(void);
VOID __stdcall apagaServico();


//	_In_ SC_HANDLE schService
//);
//VOID WINAPI SvcCtrlHandler(DWORD);
//VOID WINAPI SvcMain(DWORD, LPTSTR*);
//
//VOID ReportSvcStatus(DWORD, DWORD, DWORD);
//VOID SvcInit(DWORD, LPTSTR*);
//VOID SvcReportEvent(LPTSTR);

#endif
