#include <stdlib.h>
#include <stdio.h>

#define N 50

typedef struct pilha Pilha;
struct pilha{
    int n;
    int vet[N];
};

Pilha* pilha_cria(){
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if(p==NULL){
        exit(1);
    }
    p->n = 0; /* inicializa com zero elementos */
    return p;
}

void pilha_push(Pilha* p, int v){
    if(p->n == N){
        printf("Capacidade da pilha estourou!\n");
        exit(1);
    }
    /* insere elemento na proxima posição */
    p->vet[p->n] = v;
    p->n++;
}

int pilha_vazia(Pilha* p){
    return p->n = 0;
}

int pilha_pop(Pilha* p){
    int v;
    if(pilha_vazia(p)){
        printf("Pilha Vazia!\n");
        exit(1);
    }
    /* retira elemento do topo */
    v = p->vet[p->n-1];
    p->n--;
    return v;
}

void pilha_libera(Pilha* p){
    free(p);
    return;
}


