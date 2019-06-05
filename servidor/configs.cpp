#include "servidor.h"
//#include "../bridge/jogo.h"

extern BOLA bola;
extern SincControl sincControl;
extern JOGO configJogo;

#define CONFIG_LINE_BUFFER_SIZE 100
#define FICH_CONFIG TEXT("config2.ini")
// C program for reading 
// struct from a file 
#include <stdio.h> 
#include <stdlib.h> 


// Driver program 
int leConfig(int argc, LPTSTR argv[]) {

	FILE* infile = NULL;
	int num = 0;
	//if ((file_name = fopen(argv[1], "r")) == NULL) {

	if (argc == 2)
		_tfopen_s(&infile, argv[1], TEXT("rt, ccs=UNICODE"));
	if (infile == NULL) {
		//_tprintf(TEXT("Não foi possível carregar a configuração....\n"));
		_tprintf(TEXT("Não foi indicado ficheiro de config, vou carregar configurações por defeito ...\n"));
		//exit(1);
	}
	_tprintf(TEXT("Configuração carregada pelo ficheiro indicado...\n"));
	//	_tprintf(TEXT("Não foi indicado ficheiro de config, vou carregar configurações por defeito ...\n"));
	_tfopen_s(&infile, FICH_CONFIG, TEXT("rt, ccs=UNICODE"));

	if (infile == NULL) {
		_tprintf(TEXT("Não existe ficheiro de configuração....\n"));
		exit(1);
	}
	while (!feof(infile)) {
		//read_double_from_config_line(buf, &config.numax);
		_ftscanf_s(infile, TEXT("%d\n"), &num);
		_ftscanf_s(infile, TEXT("NUM_MAX_JOGADORES=%d\n"), &configJogo.maxJogador);
		_ftscanf_s(infile, TEXT("NUM_NIVEIS=%d\n"), &configJogo.numNiveis);
		_ftscanf_s(infile, TEXT("NUM_SPEEDUPS=%d\n"), &configJogo.numSpeedUps);
		_ftscanf_s(infile, TEXT("NUM_SLOWDOWNS=%d\n"), &configJogo.numSlowDowns);
		_ftscanf_s(infile, TEXT("DURACAO_SPEEDUPS=%d\n"), &configJogo.durSpeedUps);
		_ftscanf_s(infile, TEXT("DURACAO_SLOWDOWNS=%d\n"), &configJogo.durSlowDowns);
		_ftscanf_s(infile, TEXT("PROBAB_SPEEDUPS=%f\n"), &configJogo.probSpeedUps);
		_ftscanf_s(infile, TEXT("PROBAB_SLOWDOWNS=%f\n"), &configJogo.probSlowDowns);
		_ftscanf_s(infile, TEXT("NUM_VIDAS=%d\n"), &configJogo.numVidas);
		_ftscanf_s(infile, TEXT("NUM_TIJOLOS=%d\n"), &configJogo.numTijolos);
		_ftscanf_s(infile, TEXT("VELOCIDADE=%d\n"), &configJogo.velocidade);

		//}
	}


	_tprintf(TEXT("Configuração carregada com sucesso\n"));
	//input.fname, input.lname);

// close file 
	fclose(infile);
	//}
	return 0;
}
