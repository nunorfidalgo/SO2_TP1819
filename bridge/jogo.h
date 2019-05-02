#pragma once

#define TEXTO 120
#define NUM_BOLAS 3
#define NUM_BARREIRAS 40
#define NUM_TIJOLOS 40
#define NUM_MAX_JOGADORES 4
#define TOP_TEN 10

typedef struct {
	unsigned int x, y;
} COORDENADAS;

typedef struct {
	COORDENADAS	coord;
} BOLA;

typedef struct {
	COORDENADAS	coord;
	unsigned int cor;
} BARREIRA;

typedef struct {
	unsigned int tipo;
	unsigned int cor;
	COORDENADAS	coord;
} TIJOLO;

typedef struct {
	TCHAR nome[TEXTO];
	unsigned int pontos;
	BARREIRA barreira;
} JOGADOR;

typedef struct {
	TCHAR nome[TEXTO];
	unsigned int pontos;
} PONTUACAO;

typedef struct {
	PONTUACAO pontuacoes[TOP_TEN];
} TOPTEN;

typedef struct {
	TCHAR nome[TEXTO]; // para testar...
	/*unsigned int nivel;
	BOLA bolas[NUM_BOLAS];
	BARREIRA barreiras[NUM_BARREIRAS];
	TIJOLO tijolos[NUM_TIJOLOS];
	JOGADOR jogadores[NUM_MAX_JOGADORES];*/
} JOGO;
