#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Lista.h"
#include "FilaLista.h"
#include "PilhaLista.h"
#include "FuncoesAuxiliares.h"
#include "BibliotecaTeoGraf.h"

#define NUMERO_LINHA 1000


int main()
{
    FILE *arq;
    char Linha[NUMERO_LINHA];
    char *result;
    int numVertices;
    int numArestas = 0;
    int *vetorGraus;
    Vertice *vetorVertice;
    char **MatrizVertice;
    int *vetorMarcacao;
    char escolha;
    char nomeArq[50];
    long start, end;

    printf("Escolha o arquivo: ['as_graph.txt','dblp.txt','live_journal.txt']\n");
    scanf(" %s",nomeArq);

    printf("Deseja escolher Matriz ou Lista? [M/L] ");
    scanf(" %c",&escolha);


    // Abre um arquivo TEXTO para LEITURA
    arq = fopen(nomeArq, "rt");// ArqTeste   as_graph   dblp     live_journal
    if (arq == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return 0;
    }

    // Le a primeira linha para descobrir a quantidade de vertices totais
    result = fgets(Linha, NUMERO_LINHA-1, arq);
    result[strlen(result)-1] = '\0';
    numVertices = atoi(result); //transforma a string em inteiro

    vetorGraus = (int*) malloc(numVertices*sizeof(int));

    if(escolha == 'M' || escolha == 'm'){
        start = getMicrotime();
        MatrizVertice = geraMatrizAdjacencia(arq,Linha,result,numVertices,&numArestas, vetorGraus);
        end = getMicrotime();
//        imprimeMatriz(MatrizVertice, numVertices);
    }else if(escolha == 'L' || escolha == 'l'){
        start = getMicrotime();
        vetorVertice = geraListaAdjacencia(arq,Linha,result,numVertices, &numArestas, vetorGraus);
        end = getMicrotime();
//        imprimeListaAdjacencia(vetorVertice, numVertices);
    }else{
        printf("Porfavor, escolha novamente!");
        return 0;
    }

    fclose(arq);
    system("pause");

//    vetorMarcacao = BFSListaAdjacencia(vetorVertice, 5, numVertices);
//
//    vetorMarcacao = BFSMatriz(MatrizVertice, 5, numVertices);
//
//    vetorMarcacao = DFSListaAdjacencia(vetorVertice, 1, numVertices);
//
//    vetorMarcacao = DFSMatriz(MatrizVertice, 1, numVertices);

//    componenteConexa(vetorVertice,numVertices);

//    milCiclosListaAdjacencia(vetorVertice, numVertices, "BFS_ListaAdjacencia.txt",0); // 0(BFS) ou 1(DFS)
//    milCiclosMatriz(MatrizVertice, numVertices, "DFS_Matriz.txt",1);

//    int o;
//    o = diametroGrafo(vetorVertice, numVertices);
//    printf("Diametro: %d\n",o);

    // Calcula os Graus e gera o arquivo de Saida
    gerarGraus(vetorGraus, numVertices,numArestas,"Saida.txt");

    printf("Tempo para gerar o Grafo: %ld\n",end - start);

    return 1;
}




