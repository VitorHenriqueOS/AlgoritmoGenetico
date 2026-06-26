#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reinsecao.h"

Individuo* reinsercaoPura(Individuo *populacao, Individuo *filhos){
    if (tamanho(filhos) != POP){
        printf("Erro: O tamanho dos filhos não é igual ao tamanho da população.\n");
        return NULL; // Retorna NULL se o tamanho dos filhos não for igual ao tamanho da população
    }
    
    return filhos; // Retorna apenas os filhos, descartando os pais
}

Individuo* reinsercaoOrdenada(Individuo *populacao, Individuo *filhos){
    int t = POP + tamanho(filhos);
    Individuo *populacao_total = malloc(sizeof(Individuo) * t);

    quickSort(populacao_total, 0, t - 1);

    for (int i = 0; i < POP; i++) {
        populacao[i] = populacao_total[i];
    }
    free(populacao_total);
    return populacao;
}

Individuo* reinsercaoElitismo(Individuo *populacao, Individuo *filhos){
    int num_elitismo = POP * TaxaElitismo; // Calcula o número de indivíduos a serem mantidos

    Individuo *nova_populacao = malloc(sizeof(Individuo) * POP);

    quickSort(populacao, 0, POP - 1); // Ordena a população atual
    quickSort(filhos, 0, tamanho(filhos) - 1);

    int i;
    for (i = 0; i < num_elitismo; i++){
        nova_populacao[i] = populacao[i]; // Mantém os melhores indivíduos da população atual
    }
    for(; i < POP; i++){
        nova_populacao[i] = filhos[i - num_elitismo]; // Preenche o restante com os melhores filhos
    }
    free(populacao);
    return nova_populacao;
}