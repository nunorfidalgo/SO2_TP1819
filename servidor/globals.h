#ifndef GLOBALS_H
#define GLOBALS_H

JOGO jogo;
BOLA bola; // isto desaparece e temos que usar o jogo!!
SincControl sincControl;
SincPipes sincPipesMensagens;
SincPipes sincPipesJogo;
MENSAGEM mensagem;

HANDLE hServidor, hLogin;
HANDLE hTMensagens, hTJogo, hTBola, hTEscutaMensagens;
DWORD hTMensagensId, hTJogoId, hTBolaId, hTEscutaMensagensId;

#endif
