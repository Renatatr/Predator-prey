#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>

#define Ni 500     // tamanho da rede em x
#define Nj 500     // tamanho da rede em y
#define dt 0.1     // intervalo de tempo 
#define tf 5000    // tempo total - número de gerações
#define D 1.0      // coeficiente de mobilidade
#define p 0.25     // probabilidade de predação
#define r 0.25     // probabilidade de reprodução
