#pragma once

// Mensagens
#define TEXTO 20
#define NUM_BOLAS 3
#define NUM_BARREIRAS 40
#define NUM_TIJOLOS 40
#define NUM_MAX_JOGADORES 4
#define TOP_TEN 10

// tamanho padrão da linha de comandos do windows
#define COLUNAS 41 // x
#define LINHAS 26 // y
//
//int xp = 1, yp = LINHAS, xpa = xp;

// Estrutura de dados
// Coordenadas no mapa
typedef struct {
	unsigned int x, y;
} COORDENADAS;

// Elementos do jogo: 

// Bola
typedef struct {
	COORDENADAS	coord;
	COORDENADAS coordAnt;
} BOLA;

// Barreira
typedef struct {
	COORDENADAS	coord;
	unsigned int cor;
	COORDENADAS coordAnt;
} BARREIRA;

// TIJOLO
typedef struct {
	unsigned int tipo;
	unsigned int cor;
	COORDENADAS	coord;
} TIJOLO;

// JOGADOR
typedef struct {
	TCHAR nome[TEXTO];
	unsigned int pontos;
	BARREIRA barreira;
} JOGADOR;

// Pontuação
typedef struct {
	TCHAR nome[TEXTO];
	unsigned int pontos;
} PONTUACAO;

// Pontuações Top10
typedef struct {
	PONTUACAO pontuacoes[TOP_TEN];
} TOPTEN;

typedef struct {
	//TCHAR nome[NOME]; // para testar...
	//unsigned int nivel;
	BOLA bola;
	//BARREIRA barreiras[NUM_BARREIRAS];
	//TIJOLO tijolos[NUM_TIJOLOS];
	JOGADOR jogador;
} JOGO;
