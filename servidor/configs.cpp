#include "servidor.h"
#include "../bridge/jogo.h"

extern BOLA bola;
extern SincControl sincControl;

#define CONFIG_LINE_BUFFER_SIZE 100
#define FICH_CONFIG "..\config\config.ini"
// C program for reading 
// struct from a file 
#include <stdio.h> 
#include <stdlib.h> 


// Driver program 
int leConfig() {
	FILE* infile;
	JOGO configJogo;
	char buf[CONFIG_LINE_BUFFER_SIZE];
	// Open person.dat for reading 
	int num = 0;
	fopen_s(&infile, FICH_CONFIG, "r");

	//if (infile == NULL) {
	//	fprintf(stderr, "\nError opening file\n");
	//	exit(1);
	//}

	// read file contents till end of file    
	//while (fread(&configJogo, sizeof(configJogo), 1, infile)){
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
	}

	//	_tprintf(TEXT("NUM_MAX_JOGADORES \n"), configJogo.maxJogador);
				//input.fname, input.lname);

		// close file 
	fclose(infile);

	return 0;
}
