#include <stdlib.h>
#include <stdio.h>
#include "FilaLista.h"
#include "PilhaLista.h"
#include "Lista.h"

typedef struct vertice Vertice;
struct vertice{
    int n;
    Elemento* adjancencia;
};

typedef struct arvore Arvore;
struct arvore{
    int nivel;
    int pai;
};

typedef struct marcacao2 Marcacao2;
struct marcacao2{
    int numVertice;
    int numMarcacao;
};

void gerarArquivoArvore(Arvore *arvore, int tam){
    FILE *arqSaida;
    int i;
    if((arqSaida = fopen("Arvore.txt", "wb")) == NULL)
    {
        printf("Erro na abertura do arquivo");
        exit(1);
    }
    for(i=0;i<tam;i++){
        if(arvore[i].pai == 0){
            fprintf(arqSaida,"Vertice: %d -> Nivel: %d -> Pai: Raiz\r\n",i+1,arvore[i].nivel);
        }else{
            fprintf(arqSaida,"Vertice: %d -> Nivel: %d -> Pai: %d\r\n",i+1,arvore[i].nivel,arvore[i].pai);
        }
    }

    fclose(arqSaida);

}

int* BFSMatriz(char **Grafo, int s, int tam){
    int v,i;
    Arvore *vetorArvore = malloc(tam*sizeof(Arvore));
    int *vetorMarcacao = malloc(tam*sizeof(int));
    for(i = 0; i < tam; i++){
        vetorMarcacao[i] = 0;
    }
    vetorMarcacao[s-1]=1;
    vetorArvore[s-1].nivel = 0;
    vetorArvore[s-1].pai = 0;
    Fila *Q = fila_cria();
    fila_insere(Q,s);
    while(!fila_vazia(Q)){
        v = fila_retira(Q);
        for(i=1;i<=tam;i++){
            int w = i;
            if(Grafo[v-1][i-1]=='1'){  // Verificar se é adjacente
                if(vetorMarcacao[w-1]!=1){
                    vetorMarcacao[w-1]=1;
                    fila_insere(Q,w);
                    vetorArvore[w-1].nivel = vetorArvore[v-1].nivel + 1;
                    vetorArvore[w-1].pai = v;
                }
            }
        }
    }
    gerarArquivoArvore(vetorArvore, tam);
    return vetorMarcacao;
}

int* BFSListaAdjacencia(Vertice *Grafo, int s, int tam){
    int v,i;
    Elemento *p;
    Arvore *vetorArvore = malloc(tam*sizeof(Arvore));
    int *vetorMarcacao = malloc(tam*sizeof(int));
    for(i = 0; i < tam; i++){
        vetorMarcacao[i] = 0;
    }
    vetorMarcacao[s-1]=1;
    vetorArvore[s-1].nivel = 0;
    vetorArvore[s-1].pai = 0;
    Fila *Q = fila_cria();
    fila_insere(Q,s);
    while(!fila_vazia(Q)){
        v = fila_retira(Q);
        for(p = Grafo[v-1].adjancencia; p!= NULL; p=proximaLista(p)){
            int w = getItem(p);
            if(vetorMarcacao[w-1]==0){
//                printf("%d\n",w);
                vetorMarcacao[w-1]=1;
                fila_insere(Q,w);
                vetorArvore[w-1].nivel = vetorArvore[v-1].nivel + 1;
                vetorArvore[w-1].pai = v;
            }
        }
    }
//    gerarArquivoArvore(vetorArvore,tam);
    free(vetorArvore);
//    free(vetorMarcacao);
    return vetorMarcacao;
}

int* DFSListaAdjacencia(Vertice *Grafo, int s, int tam){
    int v,i;
    Pilha *P = pilha_cria();
    Arvore *vetorArvore = malloc(tam*sizeof(Arvore));
    int *vetorMarcacao = malloc(tam*sizeof(int));
    Elemento *p;
    for(i = 0; i < tam; i++){
        vetorMarcacao[i] = 0;
    }
    vetorArvore[s-1].nivel = 0;
    vetorArvore[s-1].pai = 0;
    pilha_push(P,s);
    while(!pilha_vazia(P)){
        v = pilha_pop(P);
        if(vetorMarcacao[v-1] != 1){
            vetorMarcacao[v-1] = 1;
            for(p = Grafo[v-1].adjancencia; p!= NULL; p=proximaLista(p)){
                int w = getItem(p);
                pilha_push(P,w);
                if(vetorMarcacao[w-1] != 1){
                    vetorArvore[w-1].nivel = vetorArvore[v-1].nivel + 1;
                    vetorArvore[w-1].pai = v;
                }
            }
        }
    }
//    gerarArquivoArvore(vetorArvore,tam);
    free(vetorArvore);
    return vetorMarcacao;
}

int* DFSMatriz(char **Grafo, int s, int tam){
    int v,i;
    Pilha *P = pilha_cria();
    Arvore *vetorArvore = malloc(tam*sizeof(Arvore));
    int *vetorMarcacao = malloc(tam*sizeof(int));
    for(i = 0; i < tam; i++){
        vetorMarcacao[i] = 0;
    }
    vetorArvore[s-1].nivel = 0;
    vetorArvore[s-1].pai = 0;
    pilha_push(P,s);
    while(!pilha_vazia(P)){
        v = pilha_pop(P);
        if(vetorMarcacao[v-1] != 1){
            vetorMarcacao[v-1] = 1;
            for(i=1;i<=tam;i++){
                int w = i;
                if(Grafo[v-1][i-1]=='1'){  // Verificar se é adjacente
                    pilha_push(P,w);
                    if(vetorMarcacao[w-1] != 1){
                        vetorArvore[w-1].nivel = vetorArvore[v-1].nivel + 1;
                        vetorArvore[w-1].pai = v;
                    }
                }
            }
        }
    }
    gerarArquivoArvore(vetorArvore,tam);
    return vetorMarcacao;
}

void BFSListaAdjacencia02(Vertice *Grafo, int s, int tam, Marcacao2* vetorMarcacao, int numMarcado){
    int v;
    Elemento *p;
    Arvore *vetorArvore = malloc(tam*sizeof(Arvore));

    vetorMarcacao[s-1].numMarcacao=numMarcado;
    vetorArvore[s-1].nivel = 0;
    vetorArvore[s-1].pai = 0;
    Fila *Q = fila_cria();
    fila_insere(Q,s);
    while(!fila_vazia(Q)){
        v = fila_retira(Q);
        for(p = Grafo[v-1].adjancencia; p!= NULL; p=proximaLista(p)){
            int w = getItem(p);
            if(vetorMarcacao[w-1].numMarcacao==0){
//                printf("%d\n",w);
                vetorMarcacao[w-1].numMarcacao=numMarcado;
                fila_insere(Q,w);
                vetorArvore[w-1].nivel = vetorArvore[v-1].nivel + 1;
                vetorArvore[w-1].pai = v;
            }
        }
    }
//    gerarArquivoArvore(vetorArvore,tam);
//    free(vetorArvore);
    return;
}



