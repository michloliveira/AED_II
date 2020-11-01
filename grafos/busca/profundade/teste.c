#include <stdio.h>
#include <stdlib.h>
#include "buscaProf.h"

int main(int argc, int* argv) {
	grafo *g;
	char origem;

    lerArq(g, "arquivo");
 	imprimir(g);
	printf("Insira uma Origem: ");
	scanf("%c",&origem);
	buscaProfundidade(g,origem);

}