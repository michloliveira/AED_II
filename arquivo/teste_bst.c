#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(int argc, char * argv[]) {
	tabela tab;
	int opcao;
	inicializarTabela(&tab);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
				case 1:
						printf("%d\n", altura(tab.indices));
						break;
				case 2:
						adicionarLivro(&tab, ler_dados());
						break;
				case 5:
						pre_order(tab.indices, &tab);
						printf("\n");
						break;
				case 6:
						in_order(tab.indices, &tab);
						printf("\n");
						break;

				case 99:
						finalizar(&tab);
						exit(0);
		}
	}
}
