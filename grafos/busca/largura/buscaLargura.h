#ifndef BUSCALARGURA_H
#define BUSCALARGURA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 100


typedef struct grafo{
    int **matriz;
    int vertices; 
	int arestas;
    char mapa[SIZE];
}grafo;


typedef struct fila{
	char vertice;
	struct fila *prox;
}fila;

fila* push(fila *fila,char v);
fila* pop (fila *fila);


void gerarMatriz(int m, grafo *graf);
void imprimirMatriz(int v, grafo *graf);
void lerArquivo(grafo *g, char* nome_arq);
void inserirMatriz(int aux1, int aux2, grafo *graf);

//int procurarInicio(grafo *g, char letraV);
void buscaLargura(grafo *g,char origem);

#endif