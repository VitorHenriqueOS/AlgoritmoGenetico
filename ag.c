#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ag.h"

Individuo* geraPopulacao(){
    Individuo *populacao = malloc(sizeof(Individuo) * POP);

    for(int i = 0; i < POP; i++){
        populacao[i] = criaIndividuo();
    }

    return populacao;
}

int fitness(Individuo *ind){
    int s = 0, e = 0, n = 0, d = 0, m = 0, o = 0, r = 0, y = 0;

    for(int i = 0; i < TAM; i++){
        switch(ind->body[i]){
            case 'S': s = i; break;
            case 'E': e = i; break;
            case 'N': n = i; break;
            case 'D': d = i; break;
            case 'M': m = i; break;
            case 'O': o = i; break;
            case 'R': r = i; break;
            case 'Y': y = i; break;
        }
    }

    return abs(((s * 1000 + e * 100 + n * 10 + d) + (m * 1000 + o * 100 + r * 10 + e)) - (m * 10000 + o * 1000 + n * 100 + e * 10 + y));
}

//====================================== Funções Auxiliares ======================================
int contem(Individuo *ind, char letra, int limite) {
    for (int i = 0; i < limite; i++) {
        if (ind->body[i] == letra) {
            return 1; // Retorna 1 (verdadeiro) se a letra já existe
        }
    }
    return 0; // Retorna 0 (falso) se a letra não foi encontrada
}

int posicaoOutro(Individuo *ind, char letra, int pos){
    for(int i = 0; i < TAM; i++){
        if(ind->body[i] == letra && i != pos)
            return i;
    }
    return -1;
}

void troca(Individuo *ind, int pos1, int pos2){

    char temp = ind->body[pos1];
    ind->body[pos1] = ind->body[pos2];
    ind->body[pos2] = temp;
}

Individuo criaIndividuo(){
    Individuo ind;

    for(int i = 0; i < TAM; i++){
        int letra;

        do{
            letra = rand() % TAM;
        }
        while(contem(&ind, Letras[letra], i));

        ind.body[i] = Letras[letra];
    }
    ind.fitness = 0;

    return ind;
}

void imprimeIndividuo(Individuo *ind){
    for(int i = 0; i < TAM; i++)
        printf("%c ", ind->body[i]);

    printf("\n");
    printf("Fitness: %d", ind->fitness);
    printf("\n");
}

int particiona(Individuo *populacao, int low, int high) {
    int pivot = populacao[high].fitness;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (populacao[j].fitness < pivot) { // Ordena em ordem crescente
            i++;
            Individuo temp = populacao[i];
            populacao[i] = populacao[j];
            populacao[j] = temp;
        }
    }

    Individuo temp = populacao[i + 1];
    populacao[i + 1] = populacao[high];
    populacao[high] = temp;

    return i + 1;
}

void quickSort(Individuo *populacao, int low, int high) {
    if (low < high) {
        int pivot = particiona(populacao, low, high);
        quickSort(populacao, low, pivot - 1);
        quickSort(populacao, pivot + 1, high);
    }

}

void embaralha(Individuo *populacao) {
    for (int i = 0; i < POP; i++) {
        int j = rand() % POP;
        Individuo temp = populacao[i];
        populacao[i] = populacao[j];
        populacao[j] = temp;
    }
}

Individuo roleta(Individuo *populacao){
    int maxFitness = populacao[0].fitness;
    
    // Encontra o pior fitness (maior valor) para usar como base
    for (int i = 1; i < POP; i++) {
        if (populacao[i].fitness > maxFitness) {
            maxFitness = populacao[i].fitness;
        }
    }

    // Calcula o total usando a diferença (inversamente proporcional)
    // Adiciona +1 para evitar que o pior indivíduo tenha chance zero absoluta se maxFitness == fitness
    long totalFitnessInvertido = 0;
    for (int i = 0; i < POP; i++) {
        totalFitnessInvertido += (maxFitness - populacao[i].fitness + 1);
    }

    if (totalFitnessInvertido == 0) return populacao[rand() % POP];

    long num = rand() % totalFitnessInvertido; 
    long soma = 0;
    int escolhido = 0;

    for (int j = 0; j < POP; j++) {
        soma += (maxFitness - populacao[j].fitness + 1);
        if (soma > num) {
            escolhido = j;
            break;
        }
    }
    return populacao[escolhido];
}

//======================================= Mutação =====================================
void mutacao(Individuo *ind) {
    int pos1 = rand() % TAM;
    int pos2 = rand() % TAM;
    
    // Garante que as posições sejam diferentes para ocorrer uma troca real
    while (pos1 == pos2) {
        pos2 = rand() % TAM;
    }
    
    troca(ind, pos1, pos2);
}

