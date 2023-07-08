#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct fila {
    char nucleotideo;
    struct fila *prox;
} Fila;

typedef struct pilha {
    char nucleotideo;
    struct pilha *prox;
} Pilha;

void insereFila(Fila **inicio, Fila **fim, char nucleotideo) {
    Fila *novo = (Fila*) malloc(sizeof(Fila));
    novo->nucleotideo = nucleotideo;
    novo->prox = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
        *fim = novo;
    } else {
        (*fim)->prox = novo;
        *fim = novo;
    }
}

void removeFila(Fila **inicio) {
    if (*inicio != NULL) {
        Fila *aux = *inicio;
        *inicio = (*inicio)->prox;
        free(aux);
    }
}

void excluirElemento(Fila **inicio, char elemento) {
    Fila *atual = *inicio;
    Fila *anterior = NULL;

    while (atual != NULL) {
        if (atual->nucleotideo == elemento) {
            if (anterior == NULL) {
                *inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Elemento %c foi removido da fila.\n", elemento);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Elemento %c n�o encontrado na fila.\n", elemento);
}

void inserePilha(Pilha **topo, char nucleotideo) {
    Pilha *novo = (Pilha*) malloc(sizeof(Pilha));
    novo->nucleotideo = nucleotideo;
    novo->prox = *topo;
    *topo = novo;
}

void removePilha(Pilha **topo) {
    if (*topo != NULL) {
        Pilha *aux = *topo;
        *topo = (*topo)->prox;
        free(aux);
    }
}

int main() {
    char dna[MAX];
    int i;

    Fila *filaInicio = NULL, *filaFim = NULL;
    Pilha *pilhaTopo = NULL;

    printf("Digite a sequ�ncia de nucleot�deos (A C T G): ");
    scanf("%s", dna);

    for (i = 0; i < strlen(dna); i++) {
        insereFila(&filaInicio, &filaFim, dna[i]);
    }

    printf("\nSequ�ncia de nucleot�deos:\n");
    Fila *filaTemp = filaInicio;
    while (filaTemp != NULL) {
        printf("%c", filaTemp->nucleotideo);
        filaTemp = filaTemp->prox;
    }
    printf("\n");

    printf("\nDupla fita do DNA:\n");
    for (i = 0; i < strlen(dna); i++) {
        switch (dna[i]) {
            case 'A':
                printf("T");
                break;

            case 'C':
                printf("G");
                break;

            case 'T':
                printf("A");
                break;

            case 'G':
                printf("C");
                break;

            default:
                printf("Nucleot�deo inv�lido!\n");
                break;
        }
    }

    char opcao;
    printf("\n\nDeseja excluir um elemento da fila? (S/N): ");
    scanf(" %c", &opcao);

    if (opcao == 'S' || opcao == 's') {
        char elemento;
        printf("Digite o elemento a ser exclu�do da fila: ");
        scanf(" %c", &elemento);

        excluirElemento(&filaInicio, elemento);

        printf("\nSequ�ncia de nucleot�deos ap�s exclus�o:\n");
        filaTemp = filaInicio;
        while (filaTemp != NULL) {
            printf("%c", filaTemp->nucleotideo);
            filaTemp = filaTemp->prox;
        }
        printf("\n");

        printf("\nDupla fita do DNA ap�s exclus�o:\n");
        for (i = 0; i < strlen(dna); i++) {
            if (dna[i] == elemento) {
                continue;
            }

            switch (dna[i]) {
                case 'A':
                    printf("T");
                    break;

                case 'C':
                    printf("G");
                    break;

                case 'T':
                    printf("A");
                    break;

                case 'G':
                    printf("C");
                    break;

                default:
                    printf("Nucleot�deo inv�lido!\n");
                    break;
            }
        }
    }

    return 0;
}

