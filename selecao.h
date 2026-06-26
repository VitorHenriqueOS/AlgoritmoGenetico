#ifndef SELECAO_H
#define SELECAO_H

#include "ag.h"

Individuo* selecaoTruncamento(Individuo *populacao);
Individuo* selecaoRoleta(Individuo *populacao);
Individuo* selecaoTorneioSimples(Individuo *populacao, int tour);
Individuo* selecaoTorneioEstocastico(Individuo *populacao, int tour);

#endif