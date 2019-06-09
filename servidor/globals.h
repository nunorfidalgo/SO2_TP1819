#ifndef GLOBALS_H
#define GLOBALS_H

JOGO jogo;

BOLA bola; // isto desaparece e temos que usar o jogo!!
SincControl sincControl;
JOGO configJogo;
HANDLE hServidor, hLogin;
HANDLE hTMensagens, hTJogo, hTBola, hTEscutaPipes;
DWORD hTMensagensId, hTJogoId, hTBolaId, hTEscutaPipesId;

SincPipes sincPipes;
MENSAGEM mensagem;

#endif
