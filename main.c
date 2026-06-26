#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ag.h"
#include "selecao.h"
#include "crossover.h"
#include "reinsercao.h"

#define NUM_TESTES 30

int main() {

	srand(time(NULL));
	int qtd_filhos = POP * TaxaCrossover; // reinserção pura tamnho == POP
	Individuo *populacao = geraPopulacao();
	Individuo *filhos = malloc(qtd_filhos * sizeof(Individuo)); 
	for(int i = 0; i < 10000; i++){
		
		// calcula o fitness dos individuos
		for(int j = 0; j < POP; j++)
			populacao[j].fitness = fitness(&populacao[j]);

		// Seleção de Pais
		Individuo *selecionados = selecaoTorneioEstocastico(populacao, 3);



		for(int j = 0; j < POP * TaxaCrossover; j+=2){
			Individuo *filhosGerados = crossoverCiclico(&selecionados[j], &selecionados[j+1]);
			filhos[j] = filhosGerados[0];
			filhos[j+1] = filhosGerados[1];
			free(filhosGerados);
		}

		// calcula o fitness dos filhos
		for(int j = 0; j < qtd_filhos; j++)
			filhos[j].fitness = fitness(&filhos[j]);
		
		populacao = reinsercaoOrdenada(populacao, filhos, qtd_filhos);
	}

	quickSort(populacao, 0, POP - 1);
	printf("Melhor individuo: ");
	imprimeIndividuo(&populacao[0]);


	free(filhos);
	free(populacao);
	return 0;
}