#include "../rps.h"

void op(int t, double *p_1, double *p_2, double *p_0); // função output.

int main(int argc, char **argv){
	int i, j, k, l, t;
	int lpx, lmx, lpy, lmy;
	double tempo, laplaciano;
	double *p_1, *p_2, *p_0;
	double *pt1, *pt2, *pt0;
	double dst1, dst2;
	FILE *file;

	p_1= (double *) calloc(Ni*Nj, sizeof(double));
	p_2= (double *) calloc(Ni*Nj, sizeof(double));
	p_0= (double *) calloc(Ni*Nj, sizeof(double));
	pt1= (double *) calloc(Ni*Nj, sizeof(double));
	pt2= (double *) calloc(Ni*Nj, sizeof(double));
	pt0= (double *) calloc(Ni*Nj, sizeof(double));

	if(argc==2){
		gsl_rng_default_seed= atoi(argv[1]); 
	}else{
		gsl_rng_default_seed= time(NULL);
	}
	gsl_rng *w= gsl_rng_alloc(gsl_rng_taus); //revervando espaço na memória para o gerador de número aleatórios

// condição inicial - começo
	for(i= 0; i< Ni; i++){
		for(j= 0; j< Nj; j++){
			k= gsl_rng_uniform(w)*3;
			switch(k){
				case 0:
					p_0[i*Ni+j]= 1.0;
				break;
				case 1:
					p_1[i*Ni+j]= 1.0;
				break;
				case 2:
					p_2[i*Ni+j]= 1.0;
				break;
			}			
		}
	}
// condição inicial - fim	
	op(0, p_1, p_2, p_0);

	for(t= 1; t<= tf; t++){
		tempo= 0.0;
		while(tempo < 1.0){
// primeiro passo de runge-kutta			
			for(i= 0; i< Ni; i++){
				for(j= 0; j< Nj; j++){
					l= i*Nj+j;
					lpx= ((i+1)%Ni)*Nj+j;
					lmx= ((i-1+Ni)%Ni)*Nj+j;
					lpy= i*Nj+(j+1)%Nj;
					lmy= i*Nj+(j-1+Nj)%Nj;
					laplaciano= p_1[lpx]+p_1[lmx]+p_1[lpy]+p_1[lmy]-4*p_1[l];
					pt1[l]= p_1[l]+0.5*dt*(D*(laplaciano)+r*p_0[l]*p_1[l]-p*p_1[l]*p_2[l]);

					laplaciano= p_2[lpx]+p_2[lmx]+p_2[lpy]+p_2[lmy]-4*p_2[l];
					pt2[l]= p_2[l]+0.5*dt*(D*(laplaciano)+r*p_0[l]*p_2[l]-p*p_2[l]*p_1[l]);
		
					laplaciano= p_0[lpx]+p_0[lmx]+p_0[lpy]+p_0[lmy]-4*p_0[l];
					pt0[l]= p_0[l]+0.5*dt*(D*(laplaciano)-r*p_0[l]*(p_1[l]+p_2[l])+p*(p_1[l]*p_2[l]+p_2[l]*p_1[l]));
				}
			}
// segundo passo de runge-kutta
			for(i= 0; i< Ni; i++){
				for(j= 0; j< Nj; j++){
					l= i*Nj+j;
					lpx= ((i+1)%Ni)*Nj+j;
					lmx= ((i-1+Ni)%Ni)*Nj+j;
					lpy= i*Nj+(j+1)%Nj;
					lmy= i*Nj+(j-1+Nj)%Nj;
					laplaciano= pt1[lpx]+pt1[lmx]+pt1[lpy]+pt1[lmy]-4*pt1[l];
					p_1[l]+= dt*(D*(laplaciano)+r*pt0[l]*pt1[l]-p*pt1[l]*pt2[l]);

					laplaciano= pt2[lpx]+pt2[lmx]+pt2[lpy]+pt2[lmy]-4*pt2[l];
					p_2[l]+= dt*(D*(laplaciano)+r*pt0[l]*pt2[l]-p*pt2[l]*pt1[l]);
	
					laplaciano= pt0[lpx]+pt0[lmx]+pt0[lpy]+pt0[lmy]-4*pt0[l];
					p_0[l]+= dt*(D*(laplaciano)-r*pt0[l]*(pt1[l]+pt2[l])+p*(pt1[l]*pt2[l]+pt2[l]*pt1[l]));
					
				}
			}
			tempo+= dt;
		}
		
		dst1= dst2= 0.0;
		for (i = 0; i < Ni*Nj; i += 1){
			dst1=+ p_1[i];
			dst2=+ p_2[i];
		}
		file= fopen("dat/dst.dat", "a");
		fprintf(file, "%e %e\n", dst1, dst2);
		fclose(file);
		
		if(t % 10 == 0){
			op(t/10, p_1, p_2, p_0);
			printf("%d\n", t);
		}
	}
	free(p_1);
	free(p_2);
	free(p_0);
	free(pt1);
	free(pt2);
	free(pt0);
	gsl_rng_free(w);
	return 0;
}
