#include "../rps.h"

void op(int t, double *p_1, double *p_2, double *p_0){
	int i, j;
	char nome[100];
	FILE *arq;
	
	sprintf(nome, "dat/phi-%d.dat", t);
	arq= fopen(nome, "w");
	for(i= 0; i< Ni; i++){
		for(j= 0; j< Nj; j++){
			fprintf(arq, "%e ", 1.0*p_1[i*Nj+j]+2.0*p_2[i*Nj+j]);
		}
		fprintf(arq, "\n");
	}
	fclose(arq);	

	sprintf(nome, "dat/emp-%d.dat", t);
	arq= fopen(nome, "w");
	for(i= 0; i< Ni; i++){
		for(j= 0; j< Nj; j++){
			fprintf(arq, "%e ", p_0[i*Nj+j]);
		}
		fprintf(arq, "\n");
	}
	fclose(arq);	
}
