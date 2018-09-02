/*
Universidade Federal do Rio de Janeiro
Escola Politecnica
Autor: Felipe Schreiber
       Matheus Moura
*/

#include <stdio.h>
#include <stdbool.h>

void addBit(char **arr,int j,int i,int V);
bool getBit(char **arr,int j,int i,int V);
void bitArrayPrint(char **arr,int V);
char **bitArrayCreator(int V,int maxBytes);
