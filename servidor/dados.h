#pragma once
#include <windows.h>
#include <locale.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

// tamanho padrão da linha de comandos do windows
#define COLUNAS 80
#define LINHAS 25

// Mensagens
#define TEXTO 20
#define NUM_BOLAS 3
#define NUM_BARREIRAS 40
#define NUM_TIJOLOS 40
#define NUM_MAX_JOGADORES 4
#define TOP_TEN 10

// Estrutura de dados
// Coordenadas no mapa
typedef struct {
	unsigned int x, y;
} COORDENADAS;

// Elementos do jogo: 

// Bola
typedef struct {
	COORDENADAS	coord;
} BOLA;

// Barreira
typedef struct {
	COORDENADAS	coord;
	unsigned int cor;
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

// Pontuações Top10
typedef struct {
	TCHAR nome[TEXTO];
	unsigned int pontos;
} TOP_TEN;

typedef struct {
	unsigned int nivel;
	BOLA bolas[NUM_BOLAS];
	BARREIRA barreiras[NUM_BARREIRAS];
	TIJOLO tijolos[NUM_TIJOLOS];
	JOGADOR jogadores[NUM_MAX_JOGADORES];
} JOGO;
