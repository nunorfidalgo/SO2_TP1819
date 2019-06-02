#include "servidor.h"
#include "../bridge/jogo.h"

extern BOLA bola;
extern SincControl sincControl;

#define CONFIG_LINE_BUFFER_SIZE 100

// C program for reading 
// struct from a file 
#include <stdio.h> 
#include <stdlib.h> 

// struct person with 3 fields 
struct person {
	int id;
	char fname[20];
	char lname[20];
};

// Driver program 
int leConfig() {
	FILE* infile;
	JOGO configJogo;
	char buf[CONFIG_LINE_BUFFER_SIZE];
	// Open person.dat for reading 
	fopen_s(&infile,"..\Config\config.ini", "r");

	if (infile == NULL) {
		fprintf(stderr, "\nError opening file\n");
		
		exit(1);
	}

	// read file contents till end of file    
	//while (fread(&configJogo, sizeof(configJogo), 1, infile))
	while (!feof(infile)) {
					//read_double_from_config_line(buf, &config.numax);
			_ftscanf_s(infile, TEXT("NUM_MAX_JOGADORES=%d\n"), configJogo.maxJogador);
			_ftscanf_s(infile, TEXT("NUM_NIVEIS=%d\n"), configJogo.numNiveis);
			_ftscanf_s(infile, TEXT("NUM_SPEEDUPS=%d\n"), configJogo.numSpeedUps);
			_ftscanf_s(infile, TEXT("NUM_SLOWDOWNS=%d\n"), configJogo.numSlowDowns);
			_ftscanf_s(infile, TEXT("DURACAO_SPEEDUPS=%d\n"), configJogo.durSpeedUps);
			_ftscanf_s(infile, TEXT("DURACAO_SLOWDOWNS=%d\n"), configJogo.durSlowDowns);
			_ftscanf_s(infile, TEXT("PROBAB_SPEEDUPS=%d\n"), configJogo.probSpeedUps);
			_ftscanf_s(infile, TEXT("PROBAB_SLOWDOWNS=%d\n"), configJogo.probSlowDowns);
			_ftscanf_s(infile, TEXT("NUM_VIDAS=%d\n"), configJogo.numVidas);
			_ftscanf_s(infile, TEXT("NUM_TIJOLOS=%d\n"), configJogo.numTijolos);
			_ftscanf_s(infile, TEXT("VELOCIDADE=%d\n"), configJogo.velocidade);
	}

		//printf("id = %d name = %s %s\n", configJogo.bola,
			//input.fname, input.lname);

	// close file 
	fclose(infile);

	return 0;
}
