#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "selecao.h"

Individuo* selecaoTruncamento(Individuo *populacao){
    Individuo *selecionados = malloc(sizeof(Individuo) * (POP * TaxaCrossover));
    quickSort(populacao, 0, POP - 1); //Ordena a população por fitness

    for(int i = 0; i < (POP * TaxaCrossover); i++){
        selecionados[i] = populacao[i]; // Seleciona os melhores indivíduos para reprodução
    }

    embaralha(selecionados); // Embaralha os selecionados, os pais serão i e i + 1

    return selecionados;
}

Individuo* selecaoRoleta(Individuo *populacao){
    Individuo *selecionados = malloc(sizeof(Individuo) * (POP * TaxaCrossover));

    for(int i = 0; i < (POP * TaxaCrossover); i++)
        selecionados[i] = roleta(populacao); // Seleciona um indivíduo usando a roleta

    return selecionados;
}


Individuo* selecaoTorneioSimples(Individuo *populacao, int tour){
    Individuo *selecionados = malloc(sizeof(Individuo) * (POP * TaxaCrossover));

    for(int i = 0; i < (POP * TaxaCrossover); i++){
        Individuo melhor = populacao[rand() % POP]; // Sorteia o primeiro competidor do torneio

        for(int j = 1; j < tour; j++){ // Realiza o torneio
            Individuo competidor = populacao[rand() % POP]; // Sorteia outro competidor

            if(competidor.fitness < melhor.fitness){ // Se o competidor for melhor que o atual vencedor...
                melhor = competidor; // ...ele se torna o novo vencedor do torneio
            }
        }

        selecionados[i] = melhor; // O vencedor do torneio é selecionado para reprodução
    }
    return selecionados;
}

Individuo* selecaoTorneioEstocastico(Individuo *populacao, int tour){
    Individuo *selecionados = malloc(sizeof(Individuo) * (POP * TaxaCrossover));

    for(int i = 0; i < (POP * TaxaCrossover); i++){
        Individuo melhor = roleta(populacao); // Sorteia o primeiro competidor do torneio usando a roleta

        for(int j = 1; j < tour; j++){ // Realiza o torneio
            Individuo competidor = roleta(populacao); // Sorteia outro competidor

            if(competidor.fitness < melhor.fitness){ // Se o competidor for melhor que o atual vencedor...
                melhor = competidor; // ...ele se torna o novo vencedor do torneio
            }
        }

        selecionados[i] = melhor; // O vencedor do torneio é selecionado para reprodução
    }
    return selecionados;
}