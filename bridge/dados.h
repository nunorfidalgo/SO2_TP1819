#pragma once

#define NOME 12

// tamanho padr�o da linha de comandos do windows
#define COLUNAS 80
#define LINHAS 25
#define MEM_PART TEXT("Nome da Mem�ria Partilhada")

// Login
typedef struct {
	TCHAR nome[NOME];
} LOGIN;

