#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "FilaVetor.h"
#include "PilhaVetor.h"

typedef struct vertice Vertice;
struct vertice{
    int n;
    Elemento* adjancencia;
};

int main()
{
    printf("Hello world!\n");

   Elemento *lst = lst_cria();
//
//    Fila* f = fila_cria();
//
//    Pilha* p = pilha_cria();

    lst = lst_insere(lst, 2);
    lst = lst_insere(lst, 22);
    lst = lst_insere(lst, 222);

    // Cria Vetor de Vertices
    Vertice ver[2];

    // Iniciar o vetor de Vertices = 0
    int i;
    for(i = 0; i < 2; i++){
        ver[i].n = 0;
    }

    ver[0].n = 1;
    ver[0].adjancencia = lst;

    for(i = 0; i < 2; i++){
        printf("%d\n", ver[i].n);
        lst_imprime(ver[i].adjancencia);
    }


    return 0;
}
