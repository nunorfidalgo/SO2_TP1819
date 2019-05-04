#pragma once

#include "jogo.h"

// Mensagem
typedef struct {
	TCHAR nome[TEXTO];
	//int jogadorx, jogadory;
	COORDENADAS coord;
	//ENTRAR entrar;
	int termina;
} MENSAGEM;
