/*
Universidade Federal do Rio de Janeiro
Escola Politecnica
Autor: Felipe Schreiber
       Matheus Moura
*/

#include <stdio.h>
#include "upperTriangleBitArray.h"
#include <stdbool.h>
#include <stdlib.h>
/*
Inputs: Essa funcao recebe a matriz triangular superior denotada por **arr, bem como o numero dos vertices que estao conectados tal como foram lidos do arquivo de input(nao importa a ordem) e o numero maximo de vertices. Importante: i e j variam de 1 ate numero maximo de vertices.

Output: Essa funcao coloca o respectivo bit da conexao em nivel 1, embora nao retorne nenhum valor.
*/
void addBit(char **arr,int j,int i,int V)
{
 int indiceReal,numberOfShifts;/*O numero do vertice nao corresponde diretamente a sua posicao na matriz, por tanto eh necessario decodifica-lo. O resultado dessa decodificacao eh armazenado em indiceReal*/
 if(i<j)/*A matriz foi codificada de tal forma que as conexoes sao representadas indo do vertice de menor indice(que eh o numero da linha) para o vertice de maior indice(que eh a coluna e a posicao do bit)*/
 {
  indiceReal = (V - j)/8;
  numberOfShifts = ((V - j)%8);
  arr[i-1][indiceReal] |= (1<<numberOfShifts);
 // printf("\nLinha:%d Coluna:%d\n",(i-1),indiceReal);
 // printf("\nNumero de shifts:%d\n",numberOfShifts); 
 }
 else
 {
  indiceReal = (V - i)/8;
  numberOfShifts = ((V - i)%8);
  arr[j-1][indiceReal] |= ( 1<<( (V - i)%8 ) );
  //printf("\nLinha:%d Coluna:%d\n",(j-1),indiceReal);
  //printf("\nNumero de shifts:%d\n",numberOfShifts);
 }
 //if(getBit(arr,j,i,V))
  //printf("\nInsercao OK\n");
}

bool getBit(char **arr,int j,int i,int V)
{
 int indiceReal;
 if(i<j)
 {
  indiceReal = (V - j)/8;//indica em qual byte se encontra o indice desejado.
  if(arr[i-1][indiceReal] & ( 1<<( (V - j)%8 ) ) )//dentro do conjunto de bytes, encontra-se o bit que representa o numero buscado
   return true;
  return false;
 }
 else
 {
  indiceReal = (V - i)/8;/*o mesmo que no caso acima, embora para o caso em que j > i.Como i eh o menor, o seu valor indicara o numero da linha e o j indicara a coluna buscada. Para encontrar a coluna buscada deve-se subtrair j do numero total de vertices, uma vez que o 1 bit de cada linha tem como destino o vertice de maior numero*/ 
  if(arr[j-1][indiceReal] & ( 1<<( (V - i)%8 ) ) )
   return true;
  return false;
 }
}

void bitArrayPrint(char **arr,int V)/*Imprime na tela como se fosse uma matriz de v² posicoes normalmente*/
{
 int i,j;
 for(i=1;i<=V;i++)
 {
  for(j=1;j<=V;j++)
  { 
   if(getBit(arr,i,j,V))
    printf("1");
   else
    printf("0");   
  }
  printf("\n");
 }  
}

char **bitArrayCreator(int V,int maxBytes)/*cria uma matriz triangular superior codificada, onde as conexoes sao representadas indo do vertice de menor indice(numero da linha) para o de maior indice. Por exemplo, se temos 4 vertices ela ficaria da forma: 
 4 3 2 1 0
0* * * * *
1* * * *
2* * *
3* *
4*

Contudo, como cada posicao da matriz sera 1 bit, dividimos a quantidade de colunas por 8. O numero maximo de bytes(ou quantidade de char ou numero maximo de colunas) eh passado para a funcao (note que o numero de colunas nao eh constante para todas as linhas: Comecando da linha zero, a cada 8 linhas esse numero eh decrementado em uma unidade. Isso faz com que retiremos todas as representacoes redundantes). Optou-se por usar uma matriz do tipo char pois contem a menor capacidade de memoria que se consegue acessar(1 byte).Entretanto, cada bit do array eh interpretado como uma coluna distinta.  
*/
{
 char **adjArray;
 int i,j,b;
 b = maxBytes;
 printf("\nnumero max de bytes:%d\n",b);
 adjArray = malloc((V)*sizeof(*adjArray));
 for(i = 0; i<V;i++)
 {
  if(((i%8) == 0) && (i != 0)){
   --maxBytes;
   //printf("\nmaxBytesCreator:%d\n",maxBytes);
  }
  adjArray[i] = malloc((maxBytes)*sizeof(*adjArray[i]));
 }
 for(i=0;i<V;i++)
 {
  if(((i%8) == 0) && (i != 0))
   --b;
  for(j=0;j<b;j++)
   adjArray[i][j] = 0; //inicializa a matriz sem nenhuma aresta, isto eh, todos os bits sao settados em zero   
 }  
 return adjArray;
}
