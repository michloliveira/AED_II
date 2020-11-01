#ifndef BUSCAPROF_H
#define BUSCAPROF_H

struct lista{
    char dado;
    struct lista *prox;
}; typedef struct lista Lista;

typedef struct grafo {
	int vertices;
	char *map;
	Lista **listaE;
} grafo;

void lerArq(grafo *g, char* nome);
void buscaProfundidade(grafo *g,char origem);
Lista* adicionarLista(Lista* l, char i);
void imprimirAdjacencias(Lista *l);
void imprimir(grafo *g);
void visitar(grafo *g, int i, int *cor, int *cont, int *d, int *f);

#endif
