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

    int i,pri,seg,ultimoCaracter;
    Vertice *vetorVertice;
    Elemento *lst;
    char* cha;
    vetorVertice = (Vertice*) malloc(numVertices * sizeof(Vertice));
    for(i = 0; i < numVertices; i++){
        vetorVertice[i].n = i+1;
        vetorVertice[i].adjancencia = lst_cria();
        vetorGraus[i] = 0;
    }

    if(numVertices > 3500000){
        cha = "	";
    }else{
        cha = " ";
    }

    printf("Vertices: %d\n",numVertices);
    i = 0;
    while (!feof(arq))
    {
        // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, NUMERO_LINHA-1, arq);  // o 'fgets' lê até NUMERO_LINHA caracteres ou até o '\n'
        ultimoCaracter = strlen(result)-1;
        // Verificar e tirar o \n caso exista
        if(result[ultimoCaracter] == '\n'){
            result[ultimoCaracter] = '\0';
        }

        pri = atoi(strtok(result,cha));
        seg = atoi(strtok('\0',cha));

        if(pri > numVertices || seg > numVertices){
//            printf("Erro! %s com numero incorreto\n", result);
            continue;
        }

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

char** geraMatrizAdjacencia(FILE *arq,char *Linha,char *result, int numVertices, int *numArestas, int *vetorGraus){
    char **MatrizVertice;
    int i,j,pri,seg,ultimoCaracter;

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
        ultimoCaracter = strlen(result)-1;
        // Verificar e tirar o \n caso exista
        if(result[ultimoCaracter] == '\n'){
            result[ultimoCaracter] = '\0';
        }
        // Transforma os numeros em inteiros
        pri = atoi(strtok(result," "));
        seg = atoi(strtok('\0'," "));

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

// Imprime o Grafo na forma de Matriz
void imprimeMatriz(int** MatrizVertice, int numVertices){
    int j,i;
    for(i = 0; i < numVertices; i++){
        for(j = 0; j< numVertices; j++){
            printf("%d ",MatrizVertice[i][j]);
        }
        printf("\n");
    }
}

// Imprime o Grafo na forma de Lista de Adjacencia
void imprimeListaAdjacencia(Vertice *vetorVertice, int numVertices){
    int i;
    for(i = 0; i < numVertices; i++){
        printf("Vertice %d: ",i+1);
        lst_imprime(vetorVertice[i].adjancencia);
        printf("\n");
    }
}
// Gera um Arquivo de Saida com o Numero Total de Vertices, Numero Total de Arestas, Grau Maximo, Grau Minimo, Grau Medio e Mediana dos Graus
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
// Executa, para Lista Adjacencia, a BFS(0) ou DFS(1) 1000x exibindo o tempo media e gerando um arquivo com o tempo em cada ciclo
void gerarArquivoTempoListaAdjacencia(Vertice *vetorVertice, int numVertices, char* nomeArquivo, int tipo){
    long start,end;
    int i;
    int *vetorMarcacao;
    double somaTempo = 0;

    FILE* s = fopen(nomeArquivo, "wb");
    fprintf(s,"Ciclo Tempo\r\n");
    if(tipo==0){
        for(i=0;i<1000;i++){
            printf("%d\n",i+1);
            start = getMicrotime();
            vetorMarcacao = BFSListaAdjacencia(vetorVertice,1,numVertices);
            end = getMicrotime();
            free(vetorMarcacao);
            somaTempo += (double) end-start;
//            fprintf(s,"%d %ld\r\n",i+1,end-start);
//          printf("Ciclo: %d -> %ld\r\n",i+1,end-start);
        }
    }
    else if(tipo==1){
        for(i=0;i<1000;i++){
            printf("%d\n",i+1);
            start = getMicrotime();
            vetorMarcacao = DFSListaAdjacencia(vetorVertice,1,numVertices);
            end = getMicrotime();
            free(vetorMarcacao);
            somaTempo += (double) (end-start);
//            fprintf(s,"%d %ld\r\n",i+1,end-start);
//          printf("Ciclo: %d -> %ld\r\n",i+1,end-start);
        }
    }else{
        fprintf(s,"Erro ao inserir o tipo de Busca. Tipos Validos: 0 (BFS) ou 1(DFS)\r\n");
        printf("Erro ao inserir o tipo de Busca. Tipos Validos: 0 (BFS) ou 1(DFS)\n");
    }

    fclose(s);
    printf("Tempo Medio: %.2f\n",somaTempo/1000);
}
// Executa, para Matriz, a BFS(0) ou DFS(1) 1000x exibindo o tempo media e gerando um arquivo com o tempo em cada ciclo
void gerarArquivoTempoMatriz(char **MatrizVertice, int numVertices, char* nomeArquivo, int tipo){
    long start,end;
    int i;
    int *vetorMarcacao;
    double somaTempo = 0;

    FILE* s = fopen(nomeArquivo, "wb");
    fprintf(s,"Ciclo Tempo\r\n");
    if(tipo==0){
        for(i=0;i<1000;i++){
//          printf("%d\n",i+1);
            start = getMicrotime();
            vetorMarcacao = BFSMatriz(MatrizVertice,1,numVertices);
            end = getMicrotime();
            free(vetorMarcacao);
            somaTempo += (double)end-start;
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
            somaTempo += (double)end-start;
            fprintf(s,"%d %ld\r\n",i+1,end-start);
//          printf("Ciclo: %d -> %ld\r\n",i+1,end-start);
        }
    }else{
        fprintf(s,"Erro ao inserir o tipo de Busca. Tipos Validos: 0 (BFS) ou 1(DFS)\r\n");
        printf("Erro ao inserir o tipo de Busca. Tipos Validos: 0 (BFS) ou 1(DFS)\n");
    }

    fclose(s);
    printf("Tempo Media: %.2f\n",somaTempo/1000);
}

void componenteConexa(Vertice *Grafo, int tam){
    int i,h,qntTotalConexo;
    int j = 1;
    int numVerticeComponenteConexa = 0;
    printf("Iniciando Componente Conexa!\n");
    // Inicializa o Vetor de Marcação que contem o numero da marcação e o numero do vertice
    Marcacao2* vetorMarcacaoCC = (Marcacao2*) malloc(tam*sizeof(Marcacao2));
    for(i = 0; i < tam; i++){
        vetorMarcacaoCC[i].numMarcacao=0;
        vetorMarcacaoCC[i].numVertice=i+1;
    }
    printf("Executando BFS!\n");
    // Executa a BFS varias vezes, marcando com o numero da componente conexa
    for(i = 0; i < tam; i++){
        if(vetorMarcacaoCC[i].numMarcacao == 0){
//            printf("%d\n",i+1);
            BFSListaAdjacencia02(Grafo,i+1,tam,vetorMarcacaoCC,j);
            j++;
        }
    }
    printf("Liberando Memoria!\n");
    // Liberar Espaco do Grafo, pois só utilizaremos o vetor de marcação
    for(i=0;i<tam;i++){
        lst_libera(Grafo[i].adjancencia);
    }
    free(Grafo);

    printf("1 MergeSort!\n");
    // Ordena o vetor de marcação em ordem crescente do numero da componente conexa
    mergeSortStruct(vetorMarcacaoCC,0,tam-1);
    qntTotalConexo = vetorMarcacaoCC[tam-1].numMarcacao;

    printf("Guardando Endereco!\n");
    // Cria um vetor para guardar a quantidade de elementos de cada componente conexa e o
    // endereco do inicio da componente conexa no vetor de marcaçao
    EndVetorPrincipal *vet = malloc(qntTotalConexo*sizeof(EndVetorPrincipal));
    for(i = 0; i < tam; i++){
        if(i == 0 || vetorMarcacaoCC[i].numMarcacao != vetorMarcacaoCC[i-1].numMarcacao){
            vet[vetorMarcacaoCC[i].numMarcacao - 1].endereco = &(vetorMarcacaoCC[i]);
        }
        numVerticeComponenteConexa++;
        if(i == tam - 1 || vetorMarcacaoCC[i].numMarcacao != vetorMarcacaoCC[i+1].numMarcacao){
            vet[vetorMarcacaoCC[i].numMarcacao - 1].qntMarcacao = numVerticeComponenteConexa;
            numVerticeComponenteConexa=0;
        }
    }

    printf("2 MergeSort!\n");
    // Ordena o vetor em ordem crescente do numero de quantidade de elemento de cada componente
    mergeSortStructEnd(vet,0,qntTotalConexo-1);

//    printf("Imprimindo...\n");
    // Imprime o numero e a quantidade de vertices de cada componente
//    for(i = qntTotalConexo - 1; i>=0; i--){
//        printf("Total: %d \n",vet[i].qntMarcacao);
//        for(h = 0; h < vet[i].qntMarcacao; h++){
//            printf("%d ",vet[i].endereco[h].numVertice);
//        }
//        printf("\n");
//    }
        printf("Qnt Total Conexo: %d\n",qntTotalConexo);
        printf("Maior Conexo: %d\n",vet[qntTotalConexo-1].qntMarcacao);
        printf("Menor Conexo: %d\n",vet[0].qntMarcacao);
//    for(i = 0; i< tam; i++){
//        printf("%d -> ",vetorMarcacaoCC[i].numMarcacao);
//    }
//    printf("\n");

}

void gerarGraus(int* vetorGraus, int numVertices, int numArestas){

    int gMax,gMin;
    float gMedio, gMediana;

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

}

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
    long start, end;

    printf("Deseja escolher Matriz ou Lista? [M/L]");
    scanf("%c",&escolha);

    // Abre um arquivo TEXTO para LEITURA
    arq = fopen("live_journal.txt", "rt");// ArqTeste   as_graph   dblp     live_journal
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
    gerarArquivoTempoListaAdjacencia(vetorVertice, numVertices, "DFS_ListaAdjacencia.txt",1); // 0(BFS) ou 1(DFS)
//    gerarArquivoTempoMatriz(MatrizVertice, numVertices, "DFS_Matriz.txt",1);

    gerarGraus(vetorGraus, numVertices,numArestas);

    printf("Tempo: %ld\n",end - start);

    return 1;
}




