#pragma once

#include "jogo.h"

// Mensagem
typedef struct {
	int termina;
	TCHAR nome[TEXTO];
	JOGADOR jogador;
} MENSAGEM;
