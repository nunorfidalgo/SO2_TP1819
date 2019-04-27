#pragma once

#define NOME 12

// tamanho padrão da linha de comandos do windows
#define COLUNAS 80
#define LINHAS 25
#define MEM_PART TEXT("Nome da Memória Partilhada")

// Login
typedef struct {
	TCHAR nome[NOME];
} LOGIN;

