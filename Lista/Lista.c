#include <stdlib.h>
#include <stdio.h>

typedef struct elemento Elemento;
struct elemento{
    int info;
    Elemento *prox;
};

/* Função de criação: retorna uma lista vazia */
Elemento* lst_cria(){
    return NULL;
}

/* Inserção no inicio: retorna a lista atualizada */
Elemento* lst_insere(Elemento *lst, int val){
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    novo->info = val;
    novo->prox = lst;
    return novo;
}

/* função imprime: imprime valores dos elementos */
void lst_imprime(Elemento *lst){
    Elemento *p;
    for(p = lst; p != NULL; p = p->prox){
        printf(" -> %d", p->info);
    }
}

/* função vazia: retorna 1 se vazia ou 0 se não vazia */
int lst_vazia(Elemento *lst){
    return lst == NULL;
}

/* função busca: busca um elemento na lista */
Elemento* busca(Elemento *lst, int v){
    Elemento *p;
    for(p = lst; p!= NULL; p=p->prox){
        if(p->info == v){
            return p;
        }
    }
    return NULL;
}

void lst_libera(Elemento *lst){
    Elemento *p = lst;
    while(p != NULL){
        Elemento *t = p->prox; /* guarda referencia para o proximo Elemento */
        free(p); /* libera a memoria apontada por p */
        p = t;  /* faz p apontar para o proximo */
    }
}

Elemento* proximaLista(Elemento *lst){
    Elemento *p = lst;
    return p->prox;
}

int getItem(Elemento *lst){
    Elemento *p = lst;
    return p->info;
}

int getTamanhoLista(Elemento *lst){
    Elemento *p;
    int tam = 0;
    for(p = lst; p != NULL; p = p->prox){
        tam++;
    }
    return tam;
}









