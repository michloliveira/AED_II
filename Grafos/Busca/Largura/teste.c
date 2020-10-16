#include <stdio.h>
#include <stdlib.h>
#include "gMatriz.h"

int main(int argc, char * argv[]) {
	grafo graf;
	char nome;
	char arquivo[15] = "grafo";//nome do arquivo a ser lido
	criarGrafo(&graf, arquivo);
	lerArquivo(&graf);
	lerVertices(&graf);
	lerArestas(&graf);
	imprimirListaAdj(&graf);

    //Busca em Largura
	scanf("%c", &nome);
	vertice* v = buscarVertice(&graf, nome);
	buscaLargura(&graf, v);
	exit(0);
}
