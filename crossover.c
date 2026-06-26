#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crossover.h"

Individuo* crossoverPMX(Individuo *pai1, Individuo *pai2){
    // 1. ALOCANDO MEMÓRIA DINÂMICA
    // Criamos um array para 2 indivíduos na Heap para que os dados não sumam ao sair da função
    Individuo *filhos = malloc(sizeof(Individuo) * 2);

    // 2. SORTEIO E ORDENAÇÃO DOS PONTOS DE CORTE
    int pos1 = rand() % TAM;
    int pos2 = rand() % TAM;

    if(pos1 > pos2) {
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }

    // 3. INICIALIZAÇÃO
    // Preenchemos os corpos com -1 para saber quais posições ainda estão "vazias"
    for(int i = 0; i < TAM; i++) {
        filhos[0].body[i] = -1;
        filhos[1].body[i] = -1;
    }

    // ==========================================
    // PASSO 1: COPIAR AS FATIAS CENTRAIS
    // ==========================================
    for(int i = pos1; i <= pos2; i++) {
        filhos[0].body[i] = pai1->body[i]; // Filho 1 recebe fatia do Pai 1
        filhos[1].body[i] = pai2->body[i]; // Filho 2 recebe fatia do Pai 2
    }

    // ==========================================
    // PASSO 2: RESOLVER MAPEAMENTO (CONFLITOS)
    // ==========================================
    
    // --- Mapeamento para o Filho 1 ---
    for(int i = pos1; i <= pos2; i++) {
        int genePai2 = pai2->body[i];
        int jaExiste = 0;
        
        for(int j = pos1; j <= pos2; j++) {
            if(filhos[0].body[j] == genePai2) {
                jaExiste = 1;
                break;
            }
        }

        if(!jaExiste) {
            int valorAtual = pai1->body[i];
            int posicaoAlvo = -1;

            while(posicaoAlvo == -1) {
                int idxPai2 = -1;
                for(int k = 0; k < TAM; k++) {
                    if(pai2->body[k] == valorAtual) {
                        idxPai2 = k;
                        break;
                    }
                }

                if(filhos[0].body[idxPai2] == -1) {
                    posicaoAlvo = idxPai2;
                } else {
                    valorAtual = filhos[0].body[idxPai2];
                }
            }
            filhos[0].body[posicaoAlvo] = genePai2;
        }
    }

    // --- Mapeamento para o Filho 2 (Lógica espelhada) ---
    for(int i = pos1; i <= pos2; i++) {
        int genePai1 = pai1->body[i];
        int jaExiste = 0;
        
        for(int j = pos1; j <= pos2; j++) {
            if(filhos[1].body[j] == genePai1) {
                jaExiste = 1;
                break;
            }
        }

        if(!jaExiste) {
            int valorAtual = pai2->body[i];
            int posicaoAlvo = -1;

            while(posicaoAlvo == -1) {
                int idxPai1 = -1;
                for(int k = 0; k < TAM; k++) {
                    if(pai1->body[k] == valorAtual) {
                        idxPai1 = k;
                        break;
                    }
                }

                if(filhos[1].body[idxPai1] == -1) {
                    posicaoAlvo = idxPai1;
                } else {
                    valorAtual = filhos[1].body[idxPai1];
                }
            }
            filhos[1].body[posicaoAlvo] = genePai1;
        }
    }

    // ==========================================
    // PASSO 3: PREENCHER AS VAGAS RESTANTES
    // ==========================================
    for(int i = 0; i < TAM; i++) {
        // Filho 1 recebe o resto do Pai 2
        if(filhos[0].body[i] == -1) {
            filhos[0].body[i] = pai2->body[i];
        }
        // Filho 2 recebe o resto do Pai 1
        if(filhos[1].body[i] == -1) {
            filhos[1].body[i] = pai1->body[i];
        }
    }

    // Retorna o ponteiro com os dois filhos gerados com sucesso
    return filhos; 
}

Individuo* crossoverCiclico(Individuo *pai1, Individuo *pai2){
    Individuo *filhos = malloc(sizeof(Individuo) * 2);

    // rastrear quais posições do cromossomo já foram preenchidas
    int visitado[TAM];
    for(int i = 0; i < TAM; i++) {
        visitado[i] = 0;
        filhos[0].body[i] = -1;
        filhos[1].body[i] = -1;
    }

    int flag_pai = 0; // Qual pai copiar o ciclo atual

    for(int i = 0; i < TAM; i++) {
        if (!visitado[i]) {
            int inicio = i;
            int atual = i;

            // Rastreia e preenche todo o ciclo atual
            do {
                visitado[atual] = 1;

                if (flag_pai == 0) {
                    // Ciclo par: Filho 1 recebe do Pai 1, Filho 2 recebe do Pai 2
                    filhos[0].body[atual] = pai1->body[atual];
                    filhos[1].body[atual] = pai2->body[atual];
                } else {
                    // Ciclo ímpar: Inverte (Filho 1 recebe do Pai 2, Filho 2 recebe do Pai 1)
                    filhos[0].body[atual] = pai2->body[atual];
                    filhos[1].body[atual] = pai1->body[atual];
                }

                // Encontra o gene do Pai 2 no Pai 1 para continuar o ciclo
                char geneAlvo = pai2->body[atual];
                for(int j = 0; j < TAM; j++) {
                    if(pai1->body[j] == geneAlvo) {
                        atual = j;
                        break;
                    }
                }

            } while (atual != inicio);

            // Alterna o pai para o próximo ciclo
            flag_pai = !flag_pai;
        }
    }

    filhos[0].fitness = 0;
    filhos[1].fitness = 0;

    return filhos;
}