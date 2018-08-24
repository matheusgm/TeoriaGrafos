#include <stdlib.h>
#include <stdio.h>

#define N 100 /* Numero maximo de elementos */

typedef struct fila Fila;
struct fila{
    int n; /* Numero de elementos na fila */
    int ini; /* posição do proximo elemento a ser retirado da fila */
    int vet[N];
};

Fila* fila_cria(){
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->n = 0; /* inicializa fila como vazia */
    f->ini = 0; /* escolhe uma posição inicial */
    return f;
}

void fila_insere(Fila *f, int v){
    int fim;
    if(f->n == N){ /* fila cheia: capacidade esgotada */
        printf("Capacidade da fila estourou!\n");
        exit(1);
    }
    /* insere elemento na proxima posição livre */
    fim = (f->ini+f->n)%N;
    f->vet[fim] = v;
    f->n++;
}

int fila_vazia(Fila *f){
    return f->n == 0;
}

int fila_retira(Fila *f){
    int v;
    if(fila_vazia(f)){
        printf("Fila Vazia!\n");
        exit(1);
    }
    /* retira elemento do inicio */
    v = f->vet[f->ini];
    f->ini = (f->ini + 1)%N;
    f->n--;
    return v;
}

void fila_libera(Fila *f){
    free(f);
    return;
}








