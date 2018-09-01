
typedef struct arvore Arvore;
typedef struct vertice Vertice;

typedef struct marcacao2 Marcacao2;

int* BFSMatriz(char **Grafo, int s, int tam);

int* BFSListaAdjacencia(Vertice *Grafo, int s, int tam);

int* DFSMatriz(char **Grafo, int s, int tam);

int* DFSListaAdjacencia(Vertice *Grafo, int s, int tam);

void gerarArquivoArvore(Arvore *arvore, int tam);

