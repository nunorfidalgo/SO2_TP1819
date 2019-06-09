#ifndef GLOBALS_H
#define GLOBALS_H

JOGO jogo;
BOLA bola; // isto desaparece e temos que usar o jogo!!
SincControl sincControl;
SincPipes sincPipes;
MENSAGEM mensagem;

HANDLE hServidor, hLogin;
HANDLE hTMensagens, hTJogo, hTBola, hTEscutaPipes;
DWORD hTMensagensId, hTJogoId, hTBolaId, hTEscutaPipesId;

#endif
