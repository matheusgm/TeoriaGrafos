#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Lista.h"
#include "FilaLista.h"
#include "PilhaLista.h"
#include "Busca.h"
#include "FuncoesAuxiliares.h"

#define NUMERO_LINHA 1000

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

typedef struct endVetorPrincipal EndVetorPrincipal;
struct endVetorPrincipal{
    int qntMarcacao;
    Marcacao2* endereco;
};

 Vertice* geraListaAdjacencia(FILE *arq,char *Linha,char *result, int numVertices, int *numArestas, int *vetorGraus){

    int i;
    int pri;
    int seg;

    Vertice *vetorVertice;
    vetorVertice = malloc(numVertices * sizeof(Vertice));

    for(i = 0; i < numVertices; i++){
        vetorVertice[i].n = i+1;
        vetorVertice[i].adjancencia = lst_cria();
        vetorGraus[i] = 0;
    }
    printf("Vertices: %d\n",numVertices);
    i = 0;
    while (!feof(arq))
    {
        // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, NUMERO_LINHA-1, arq);  // o 'fgets' lê até NUMERO_LINHA caracteres ou até o '\n'
        int ultimoCaracter = strlen(result)-1;
        // Verificar e tirar o \n caso exista
        if(result[ultimoCaracter] == '\n'){
            result[ultimoCaracter] = '\0';
        }
//        printf("%s\n",result); // 1 397 510
                                 // 1397374 1397389

        pri = atoi(strtok(result," "));
        seg = atoi(strtok('\0'," "));

//        printf("Linha %d - %d %d\n",i+1,pri,seg);
        if(pri > numVertices || seg > numVertices){
            printf("Erro! %s com numero incorreto\n", result);
            continue;
        }

        Elemento *lst;
        // Insere o segundo vertice na lista adjacencia do primeiro vertice
        lst = vetorVertice[pri-1].adjancencia;
        lst = lst_insere(lst,seg);
        vetorVertice[pri-1].adjancencia = lst;

        // Insere o primeiro vertice na lista adjacencia do segundo vertice
        lst = vetorVertice[seg-1].adjancencia;
        lst = lst_insere(lst,pri);
        vetorVertice[seg-1].adjancencia = lst;

        vetorGraus[pri-1]++;
        vetorGraus[seg-1]++;

        i++;
        (*numArestas)++;
    }
//    printf("Chegou Aqui\n");

    return vetorVertice;
}

char** geraMatrizAdjacenciaCHAR(FILE *arq,char *Linha,char *result, int numVertices, int *numArestas, int *vetorGraus){
    char **MatrizVertice;
    int i,j;
    int pri;
    int seg;
    MatrizVertice = (char**) malloc(numVertices*sizeof(char*));
    for(i = 0; i < numVertices; i++){
//        printf("%d\n",i);
        MatrizVertice[i] = (char*) malloc(numVertices*sizeof(char));
        vetorGraus[i] = 0;
        for(j = 0; j < numVertices; j++){
            MatrizVertice[i][j] = '0';
        }
    }
    i = 0;
    while (!feof(arq))
    {
        // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, NUMERO_LINHA-1, arq);  // o 'fgets' lê até NUMERO_LINHA caracteres ou até o '\n'
        int ultimoCaracter = strlen(result)-1;
        // Verificar e tirar o \n caso exista
        if(result[ultimoCaracter] == '\n'){
            result[ultimoCaracter] = '\0';
        }
//        printf("%s\n",result);
        pri = atoi(strtok(result," "));
        seg = atoi(strtok('\0'," "));
//        printf("Linha %d - %d %d\n",i+1,pri,seg);

        if(pri > numVertices || seg > numVertices){
            printf("Erro! %s com numero incorreto\n", result);
            continue;
        }

        MatrizVertice[pri-1][seg-1] = '1';
        MatrizVertice[seg-1][pri-1] = '1';

        vetorGraus[pri-1]++;
        vetorGraus[seg-1]++;

        i++;
        (*numArestas)++;
    }




    return MatrizVertice;
}

void imprimeMatriz(int** MatrizVertice, int numVertices){
    int j,i;
    for(i = 0; i < numVertices; i++){
        for(j = 0; j< numVertices; j++){
            printf("%d ",MatrizVertice[i][j]);
        }
        printf("\n");
    }
}

void imprimeListaAdjacencia(Vertice *vetorVertice, int numVertices){
    int i;
    for(i = 0; i < numVertices; i++){
        printf("Vertice %d: ",i+1);
        lst_imprime(vetorVertice[i].adjancencia);
        printf("\n");
    }
}

void gerarArquivoSaida(int numeroVertice, int numArestas, int gMax, int gMin, float gMediana, float gMedio){
    FILE *arqSaida;
    if((arqSaida = fopen("Saida.txt", "wb")) == NULL)
    {
        printf("Erro na abertura do arquivo");
        exit(1);
    }

    fprintf(arqSaida,"Numero de Vertices: %d\r\n",numeroVertice);
    fprintf(arqSaida,"Numero de Arestas: %d\r\n", numArestas);
    fprintf(arqSaida,"Grau Minimo: %d\r\n",gMin);
    fprintf(arqSaida,"Grau Maximo: %d\r\n",gMax);
    fprintf(arqSaida,"Grau Media: %.2f\r\n",gMedio);
    fprintf(arqSaida,"Mediana do Grau: %.2f\r\n",gMediana);

    fclose(arqSaida);

}

void gerarArquivoTempoListaAdjacencia(Vertice *vetorVertice, int numVertices, char* nomeArquivo, int tipo){
    long start,end;
    int i;
    int *vetorMarcacao;
    long somaTempo = 0;

    FILE* s = fopen(nomeArquivo, "wb");
    fprintf(s,"Ciclo Tempo\r\n");
    if(tipo==0){
        for(i=0;i<1000;i++){
//        printf("%d\n",i+1);
        start = getMicrotime();
        vetorMarcacao = BFSListaAdjacencia(vetorVertice,1,numVertices);
        end = getMicrotime();
        free(vetorMarcacao);
        somaTempo += end-start;
        fprintf(s,"%d %ld\r\n",i+1,end-start);
//        printf("Ciclo: %d -> %ld\r\n",i+1,end-start);
        }
    }
    else if(tipo==1){
        for(i=0;i<1000;i++){
//        printf("%d\n",i+1);
        start = getMicrotime();
        vetorMarcacao = DFSListaAdjacencia(vetorVertice,1,numVertices);
        end = getMicrotime();
        free(vetorMarcacao);
        somaTempo += end-start;
        fprintf(s,"%d %ld\r\n",i+1,end-start);
//        printf("Ciclo: %d -> %ld\r\n",i+1,end-start);
        }
    }else{
        fprintf(s,"Erro ao inserir o tipo de Busca. Tipos Validos: 0 (BFS) ou 1(DFS)\r\n");
        printf("Erro ao inserir o tipo de Busca. Tipos Validos: 0 (BFS) ou 1(DFS)\n");
    }

    fclose(s);
    printf("Tempo Media: %.2f",(float)somaTempo/1000);
}

void gerarArquivoTempoMatriz(char **MatrizVertice, int numVertices, char* nomeArquivo, int tipo){
    long start,end;
    int i;
    int *vetorMarcacao;

    FILE* s = fopen(nomeArquivo, "wb");
    fprintf(s,"Ciclo Tempo\r\n");
    if(tipo==0){
        for(i=0;i<1000;i++){
//          printf("%d\n",i+1);
            start = getMicrotime();
            vetorMarcacao = BFSMatriz(MatrizVertice,1,numVertices);
            end = getMicrotime();
            free(vetorMarcacao);
            fprintf(s,"%d %ld\r\n",i+1,end-start);
//          printf("Ciclo: %d -> %ld\r\n",i+1,end-start);
        }
    }
    else if(tipo==1){
        for(i=0;i<1000;i++){
//          printf("%d\n",i+1);
            start = getMicrotime();
            vetorMarcacao = DFSMatriz(MatrizVertice,1,numVertices);
            end = getMicrotime();
            free(vetorMarcacao);
            fprintf(s,"%d %ld\r\n",i+1,end-start);
//          printf("Ciclo: %d -> %ld\r\n",i+1,end-start);
        }
    }else{
        fprintf(s,"Erro ao inserir o tipo de Busca. Tipos Validos: 0 (BFS) ou 1(DFS)\r\n");
        printf("Erro ao inserir o tipo de Busca. Tipos Validos: 0 (BFS) ou 1(DFS)\n");
    }

    fclose(s);

}

void componenteConexa(Vertice *Grafo, int tam){
    int i;
    int j = 1;
    Marcacao2* vetorMarcacaoCC = (Marcacao2*) malloc(tam*sizeof(Marcacao2));
    for(i = 0; i < tam; i++){
        vetorMarcacaoCC[i].numMarcacao=0;
        vetorMarcacaoCC[i].numVertice=i+1;
    }

    for(i = 0; i < tam; i++){
        if(vetorMarcacaoCC[i].numMarcacao == 0){
            BFSListaAdjacencia02(Grafo,i+1,tam,vetorMarcacaoCC,j);
            j++;
        }
    }

    mergeSortStruct(vetorMarcacaoCC,0,tam-1);
    int maxConexo = vetorMarcacaoCC[tam-1].numMarcacao;

    EndVetorPrincipal *vet = malloc(maxConexo*sizeof(EndVetorPrincipal));
    int x = 0;
    for(i = 0; i < tam; i++){
        if(i == 0 || vetorMarcacaoCC[i].numMarcacao != vetorMarcacaoCC[i-1].numMarcacao){
            vet[vetorMarcacaoCC[i].numMarcacao - 1].endereco = &(vetorMarcacaoCC[i]);
        }
        x++;
        if(i == tam - 1 || vetorMarcacaoCC[i].numMarcacao != vetorMarcacaoCC[i+1].numMarcacao){
            vet[vetorMarcacaoCC[i].numMarcacao - 1].qntMarcacao = x;
            x=0;
        }
    }

    mergeSortStructEnd(vet,0,maxConexo-1);

    int h;
    for(i = maxConexo - 1; i>=0; i--){
        printf("Total: %d \n",vet[i].qntMarcacao);
        for(h = 0; h < vet[i].qntMarcacao; h++){
            printf("%d ",vet[i].endereco[h].numVertice);
        }
        printf("\n");
    }

//    for(i = 0; i< tam; i++){
//        printf("%d -> ",vetorMarcacaoCC[i].numMarcacao);
//    }
//    printf("\n");

}



int main()
{
    FILE *arq;
    char Linha[NUMERO_LINHA];
    char *result;
    int numVertices;
    int numArestas = 0;
    int gMax,gMin;
    float gMedio, gMediana;
    int *vetorGraus;
    Vertice *vetorVertice;
    char **MatrizVertice;
    int *vetorMarcacao;
    char escolha;
    long start, end;

    printf("Deseja escolher Matriz ou Lista? [M/L]");
    scanf("%c",&escolha);

    // Abre um arquivo TEXTO para LEITURA
    arq = fopen("dblp.txt", "rt");// ArqTeste   as_graph   dblp     live_journal
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
        MatrizVertice = geraMatrizAdjacenciaCHAR(arq,Linha,result,numVertices,&numArestas, vetorGraus);
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

//    vetorMarcacao = BFSListaAdjacencia(vetorVertice, 1, numVertices);
//
//    vetorMarcacao = BFSMatriz(MatrizVertice, 1, numVertices);
//
//    vetorMarcacao = DFSListaAdjacencia(vetorVertice, 1, numVertices);
//
//    vetorMarcacao = DFSMatriz(MatrizVertice, 1, numVertices);
//    int i;
//    for(i = 0; i < numVertices; i++){
//        printf("Vetor %d -> %d\n",i+1,vetorMarcacao[i]);
//    }
//    componenteConexa(vetorVertice,numVertices);
    gerarArquivoTempoListaAdjacencia(vetorVertice, numVertices, "BFS_ListaAdjacencia.txt",0); // 0(BFS) ou 1(DFS)
//    gerarArquivoTempoMatriz(MatrizVertice, numVertices, "BFS_Matriz.txt",0);

    mergeSort(vetorGraus,0,numVertices-1);
    gMax = vetorGraus[numVertices-1];
    gMin = vetorGraus[0];

    if(numVertices % 2 == 0){
        gMediana = (float)(vetorGraus[(int)(numVertices/2)] + vetorGraus[(int)(numVertices/2) + 1])/2;
    }else{
        gMediana = (float)vetorGraus[(int)(numVertices/2)];
    }

    gMedio = (numArestas*2)/(float)numVertices;

    gerarArquivoSaida(numVertices, numArestas, gMax, gMin, gMediana, gMedio);

    printf("Tempo: %ld\n",end - start);

    return 1;
}




