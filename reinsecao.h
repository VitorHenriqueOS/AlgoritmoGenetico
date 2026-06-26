#ifndef REINSECAO_H
#define REINSECAO_H

#include "ag.h"

Individuo* reinsercaoPura(Individuo *populacao, Individuo *filhos);
Individuo* reinsercaoUniforme(Individuo *populacao, Individuo *filhos, int num_filhos); //Não sera usada
Individuo* reinsercaoOrdenada(Individuo *populacao, Individuo *filhos);
Individuo* reinsercaoElitismo(Individuo *populacao, Individuo *filhos);


#endif