#ifndef AG_H
#define AG_H

#define TAM 10
#define POP 100
#define Geracoes 50
#define TaxaCrossover 0.6
#define TaxaMutacao 0.01
#define TaxaElitismo 0.2
#define Letras "SENDMORY-_" 

typedef struct {
    char body[TAM];
    int fitness;
} Individuo;

Individuo criaIndividuo();
Individuo* geraPopulacao();
int fitness(Individuo *ind);
void mutacao(Individuo *ind);

int particiona(Individuo *populacao, int low, int high);
void quickSort(Individuo *populacao, int low, int high);
Individuo roleta(Individuo *populacao);
void embaralha(Individuo *populacao);
void troca(Individuo *ind, int pos1, int pos2);
int contem(Individuo *ind, char letra, int limite);


void imprimeIndividuo(Individuo *ind);


#endif 