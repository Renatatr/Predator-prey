//criado em      :2018/07/02
//ult. atualizção:2019/07/02
//autora         :renata <renatatrintin@gmail.com>
//notas          :faz a média de cada coluna
//compilação     :gcc -O3 media.c -static -lgsl -lgslcblas -lm -o media.out
//execução       :./media.out n_linhas n_colunas

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_statistics.h>

int main (int argc, char *argv[]){
	
	int i, f, a, l;
	double **x;
	double *med;
	char nome[100];

	l= atoi(argv[1]);	
	a= atoi(argv[2]);

	x = (double **) calloc(a, sizeof(double *));
	for (i= 0; i < a; i+= 1){
  		x[i] = (double *) calloc(l, sizeof(double ));
	}

	med= (double *) calloc(l, sizeof(double ));

	FILE *arquivo;
	
	arquivo= fopen("dst.dat", "r");
	for (f = 0; f < l; f += 1){
		fscanf(arquivo, "%lf %lf %lf", &x[0][f], &x[1][f], &x[2][f]);
	}
	fclose(arquivo);

	arquivo= fopen("media.dat", "w");
	for (i = 0; i < a; i += 1){	
		for (f = 0; f < l; f += 1){		
			med[f]= x[i][f];
		}
		fprintf(arquivo, "%e ", gsl_stats_mean(med, 1, l));	
	}
	fclose(arquivo);

	for (f = 0; f < a; f += 1){
		free(x[f]);
	}

	free(x);
	free(med);
	
	return 0;
}
