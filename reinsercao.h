#ifndef REINSERCAO_H
#define REINSERCAO_H

#include "ag.h"

Individuo* reinsercaoPura(Individuo *populacao, Individuo *filhos, int num_filhos);
Individuo* reinsercaoUniforme(Individuo *populacao, Individuo *filhos, int num_filhos); //Não sera usada
Individuo* reinsercaoOrdenada(Individuo *populacao, Individuo *filhos, int num_filhos);
Individuo* reinsercaoElitismo(Individuo *populacao, Individuo *filhos, int num_filhos);


#endif