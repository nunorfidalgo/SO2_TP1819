#ifndef GLOBALS_H
#define GLOBALS_H

JOGO jogo;

BOLA bola; // isto desaparece e temos que usar o jogo!!
SincControl sincControl;

HANDLE hServidor, hLogin;
HANDLE hTMensagens, hTJogo, hTBola;
DWORD hTMensagensId, hTJogoId, hTBolaId;

#endif
