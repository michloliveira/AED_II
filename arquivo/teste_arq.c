#include <stdio.h>
#include <stdlib.h>
#include "arq.h"

int main(int argc, char * argv[]) {
	tabela tab;
	int opcao;
	inicializarTabela(&tab);

	while(1) {
		printf("1 - Buscar Livro\n2 - Inserir Livro\n3 - Listar Livros\n99 - Salvar e Sair\n");
		scanf("%d", &opcao);
		switch(opcao) {
				int valor;
				case 1:
						printf("Digite o código do livro a ser buscado:\n");
						scanf("%d",&valor);
						buscar(valor,tab.indices, &tab);
						printf("\n");
						break;
				case 2:
						adicionarLivro(&tab, ler_dados());
						break;
				case 3:
						printf("\n");
						in_order(tab.indices, &tab);
						printf("\n");
						break;

				case 99:
						finalizar(&tab);
						exit(0);
		}
	}
}
