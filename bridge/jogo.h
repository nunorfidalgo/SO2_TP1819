#pragma once

#include "pipes.h"

#define TEXTO 120
#define TOP_TEN 10

typedef struct {
	unsigned int x, y;
} COORDENADAS;

typedef struct {
	COORDENADAS	coord;
	COORDENADAS direcao;
} BOLA;

typedef struct {
	unsigned int tipo;
	unsigned int cor;
	COORDENADAS	coord;
} TIJOLO;

typedef struct {
	COORDENADAS	coord;
} BARREIRA;

typedef struct {
	TCHAR nome[TEXTO];
	unsigned int cor;
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
	//TCHAR nome[TEXTO]; // para testar...
	//unsigned int nivel;
	//BOLA bolas[NUM_BOLAS];
	//BARREIRA barreiras[NUM_BARREIRAS];
	//TIJOLO tijolos[NUM_TIJOLOS];
	//JOGADOR jogadores[NUM_MAX_JOGADORES];
	BOLA bola;
	JOGADOR jogadores[N_PIPES];
	int termina;
	int maxJogador;//MAX_JOGADORES = 20
	int numNiveis;//NUM_NIVEIS = 3
	int numSpeedUps;//NUM_SPEEDUPS = 3
	int numSlowDowns;//NUM_SLOWDOWNS = 3
	int durSpeedUps;//DURACAO_SPEEDUPS = 10
	int durSlowDowns;//DURACAO_SLOWDOWNS = 10
	float probSpeedUps;//PROBAB_SPEEDUPS = 10
	float probSlowDowns;//PROBAB_SLOWDOWNS = 5
	int numVidas;//NUM_VIDAS = 3
	int numTijolos;//NUM_TIJOLOS = 15
	int velocidade;//VELOCIDADE = 100
} JOGO;
