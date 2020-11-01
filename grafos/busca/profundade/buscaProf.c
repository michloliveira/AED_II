#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buscaProf.h"

#define BRANCO 0
#define CINZA 1
#define PRETO 2

void lerArq(grafo *g, char* nome){
	FILE *arq;
	arq = fopen(nome, "r");

	if(arq != NULL){
		char buffer[20];
		char aux[20];
		fgets(buffer, 19, arq);
		char *vert = strtok(buffer," "); 
		char *are = strtok(NULL, "\n");
		g->vertices = atoi(vert);

		g->map = (char *) malloc(sizeof(char) * g->vertices);
		g->listaE = (Lista **) malloc(sizeof(Lista*) * g->vertices);	

		for(int i = 0; i < g->vertices; i++){ 
			fscanf(arq,"%c",&g->map[i]);
			if(g->map[i] == '\n'){
				i--;
			}
		}

		while(fgets(aux, 19, arq) != NULL){ 
			char primeiro, segundo;
			int valorA, valorB, verdade = 0;

			for(int i = 0; i < g->vertices; i++){
				if(aux[0] == g->map[i]){
					primeiro = g->map[i];
					valorA = i;
					verdade += 1;
				}
				if(aux[1] == g->map[i]){
					segundo = g->map[i];
					valorB = i;	
					verdade += 1;
				}  
				if(verdade == 2){
					g->listaE[valorA] = adicionarLista(g->listaE[valorA], segundo);
					g->listaE[valorB] = adicionarLista(g->listaE[valorB], primeiro);

					verdade = 0;
				}			                   
			}
		}
		fclose(arq);
	}
	else{
		printf("Arquivo de leitura inexistente!\n");
		exit(0);
	}
}
void visitar(grafo *g, int i, int *cor, int *cont, int *d, int *f){
	int j, chave;	
	cor[i] = CINZA;
	*cont = *cont + 1;
	d[i] = *cont;

	printf("-> %c ",g->map[i]); //Imprime o vertice que está visitando

	Lista *v = g->listaE[i];
 	while(v != NULL){
		for(j = 0; j < g->vertices; j++){
			if(g->map[j] == v->dado){
				chave = j;	
			}		
		}		
				
		if(cor[chave] == BRANCO){
			visitar(g, chave, cor, cont, d, f);		
		}
		v = v->prox;
	}
	cor[i] = PRETO;
	*cont++;	
	f[i] = *cont;
}

Lista* adicionarLista(Lista* l, char i){
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo->dado = i;
    novo->prox = l;
    return novo;
}

void imprimirAdjacencias(Lista *l){
    Lista *p;
    for(p = l; p != NULL; p = p->prox){
            printf("%c ", p->dado);
    }
}

void imprimir(grafo *g) {
		Lista **aux;

		aux = g->listaE;
		printf("Lista de Adjacencias\n");
		for(int i =0; i < g->vertices; i++) {
				printf("%c: ", g->map[i]);
				imprimirAdjacencias(g->listaE[i]);					
				printf("\n");
		}
}

void buscaProfundidade(grafo *g,char origem){	
	int *cor = (int *) malloc(sizeof(int) * g->vertices);
	int i; 
	int cont = 0;
	int *d = (int *) malloc(sizeof(int) * g->vertices);
	int *f = (int *) malloc(sizeof(int) * g->vertices);
		
	for(i = 0; i < g->vertices; i++){//init , todos os vertices com a cor branca
		cor[i] = BRANCO;
	}
	for(i = 0; i < g->vertices; i++){
		if(origem == g->map[i] && cor[i] == BRANCO ){
			visitar(g, i, cor, &cont, d, f);		
		}	
	}
	for(i = 0; i < g->vertices; i++){
		if(cor[i] == BRANCO ){
			printf("\nOrigem: %c\n",g->map[i]);
			visitar(g, i, cor, &cont, d, f);
			printf("\n");		
		}	
	}
	printf("\n");
}