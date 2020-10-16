#include "gMatriz.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void lerArquivo(grafo *g){ // ler vertices ,arestas do arquivo
	char *aux;
	char buffer[16];
	fgets(buffer, 15, g->arq);
	aux = strtok(buffer," ");
	if(aux != NULL){
		g->vertices = atoi(aux);
		aux = strtok(NULL,"\n");
		g->arestas = atoi(aux);
	}
}
void criarGrafo(grafo *g, char *nome){
	g->nome = strdup(nome);
	g->arq = fopen(nome, "r");
	if(g->arq == NULL){
	printf("Arquivo não encontrado");    
		exit(1);
	}
	for(int i=0; i<100; i++){
		g->elementos[i] = NULL;
	}
}
vertice* carregarVertices(grafo *g){
	int i;
	vertice* aux = (vertice*)malloc(sizeof(vertice));
	aux->ID = fgetc(g->arq);
	fgetc(g->arq);
	aux->adjacentes = (char*)malloc(g->vertices * sizeof(char));
	for(i=0; i < g->vertices; i++){
		aux->adjacentes[i] = '\0';
	}
	return aux;
}

void lerVertices(grafo *g){
	int i, j;
	for(i=0; i < g->vertices; i++){
		vertice* aux = carregarVertices(g);
		g->elementos[i] = aux;
	}
}

void lerArestas(grafo *g){
	int i, j;
	vertice *aux;
	char v1, v2;
	for(i = 0; i < g->arestas; i++){
		v1 = fgetc(g->arq);
		v2 = fgetc(g->arq);
		fgetc(g->arq);
		for(i = 0; i<100; i++){
			aux = g->elementos[i];
			if((aux == NULL)||(aux->ID == v1)){
				break;
			}
		}    
		for(j=0; aux != NULL && aux->adjacentes[j] != '\0'; j++);
		if(aux != NULL){
			aux->adjacentes[j] = v2;
		}
		if(v1 != v2){
			for(i=0; i<100; i++){
				aux = g->elementos[i];
				if((aux == NULL)||(aux->ID == v2)){
					break;
				}
		    	} 
		    	for(j=0; aux != NULL && aux->adjacentes[j] != '\0'; j++);
		    	if(aux != NULL){
		    		aux->adjacentes[j] = v1;
		    	}
		}
	}
}

void imprimirListaAdj(grafo *g){
	int i, j;
	vertice *aux;
	for(i=0; aux != NULL && i < g->vertices; i++){
		aux = g->elementos[i];		
		printf("%c: ", aux->ID);
		j = 0;
		while(aux->adjacentes[j] != '\0'){
			printf("%c ", aux->adjacentes[j]);
			j++;
		}
		printf("\n");	
	}
}

fila* Push_Fila(fila *aux, vertice *v){
	fila *nova = aux;
	if(nova == NULL){
		nova = (fila*)malloc(sizeof(fila));
		nova->vert = v;
		nova->prox = NULL;
		return nova;
	}
	if(nova->prox == NULL){
		nova->prox = (fila*)malloc(sizeof(fila));
		nova->prox->vert = v;
		nova->prox->prox = NULL;
		return nova;		
	}
	nova->prox = Push_Fila(nova->prox, v);
	return nova;
}

fila* Pop_Fila(fila *aux){
	fila* nova = aux;
	if(nova == NULL){
		return NULL;
	}
	if(nova->prox == NULL){
		return NULL;
	}
	return nova->prox;
}

vertice* buscarInicio(fila *aux){
	fila* f = aux;
	if(f == NULL){
		return NULL;
	}
	if(f->vert != NULL){
		return f->vert;
	}
}

vertice* buscarVertice(grafo *g, char nome){
  vertice* aux;
  for(int i = 0; i<100; i++){
	aux = g->elementos[i];    
	if(aux->ID == nome){
      		return aux;
    	}
  }
  return NULL;
}

void buscaLargura(grafo *g, vertice *s){
	fila* pi = NULL;	
	vertice* aux;
	int i = 0;
	int j, k;
	int cor[g->vertices];
	vertice* pai[g->vertices];
	vertice* vert[g->vertices];
	for(i = 0; i<g->vertices; i++){
		aux = g->elementos[i];	
		aux->cor = 0;
		aux->pai = NULL;
		if(aux->ID == s->ID){
			j = i;
		}
		i++;
	}
	aux = g->elementos[j];
	aux->cor = 1;
	pi = Push_Fila(pi, s);
	int posicao = 0;
	while(pi != NULL){
		aux = buscarInicio(pi);
		for(i=0; i<g->vertices; i++){		
			if(g->elementos[i]->ID == aux->ID){
				posicao = i;
			}
		}
		for(i=0; i<g->vertices; i++){
			for(j=0; j<g->vertices; j++){
				if((aux->adjacentes[j] == g->elementos[i]->ID)&&(g->elementos[i]->cor==0)){		
					g->elementos[i]->cor = 1;
					g->elementos[i]->pai = aux;
					vertice* go = buscarVertice(g, aux->adjacentes[j]);
					pi = Push_Fila(pi, go);
				}
			}
		}
		pi = Pop_Fila(pi);
		g->elementos[posicao]->cor = 2;		
	}
	printf("A partir do vertice %s:\n", &s->ID);
	for(i=0; i < g->vertices; i++){
		if((g->elementos[i]->cor == 2) && (g->elementos[i]->ID != s->ID)){
			printf("%s\n", &g->elementos[i]->ID);
		}
	}
}
