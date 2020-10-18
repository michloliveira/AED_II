#ifndef BUSCALARGURA_H
#define BUSCALARGURA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 100


typedef struct grafo{
    int **matriz;
    char map[SIZE];
    int vertices; 
	int arestas;
}grafo;


typedef struct fila{
	char v;
	struct fila *prox;
}fila;

fila* push(fila *fila,char v);
fila* pop (fila *fila);


void gerarMatriz(int m, grafo *graf);
void imprimeMatriz(int v, grafo *graf);
void lerArq(grafo *g, char* nome_arq);
void insereMatriz(int aux1, int aux2, grafo *graf);
void buscaLargura(grafo *g,char origem);

#endif