#include "buscaLargura.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void gerarMatriz(int m, grafo *graf){
    int **mat;

    mat = (int**) malloc(m * sizeof(int*)); // colunas

    for(int i = 0; i < m; i++){
        mat[i] = (int*) malloc(m * sizeof(int)); //linhas
    }
    graf->matriz = mat;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            if(i == j){ //caso os valores sejam o mesmo, colocar 1, para ter a linha diagrafonal na matriz
                graf->matriz[i][j] = 1; 
            }
            else{ //senãao, atribuir tudo a 0
                graf->matriz[i][j] = 0;
            }
        }
    }
    return;
}
void imprimirMatriz(int m, grafo *graf){
    printf("MATRIZ:\n ");
    printf(" ");
    for(int k = 0; k <  m; k++){ //printar a primeira com os valores dos vertices
        printf("%c ",graf->mapa[k]);
    }
    printf("\n");
    for(int i = 0; i < m; i++){ // printar o restante da matriz
        printf("%c ",graf->mapa[i]);
        for(int j = 0; j < m; j++){
            printf("%d ", graf->matriz[i][j]);
        }
        printf("\n");
    }
}
void lerArquivo(grafo *graf, char* nome_arq){

    FILE *arq;
    arq = fopen(nome_arq, "r"); 
    char buffer[20];
    fgets(buffer, 19, arq);
    char *vertices = strtok(buffer," "); //divide a string por espaço
    char *arestas = strtok(NULL, "\n"); //limpa a buffer ler até o \n

    char lista[atoi(vertices)];
    for(int i = 0; i < sizeof(lista); i++){ // adicionar na lista de vertices
        fscanf(arq,"%c",&lista[i]);
        if(lista[i] == '\n'){
            i--;
        } 
    }
    graf->vertices = atoi(vertices);
    graf->arestas = atoi(arestas);
    strcpy(graf->mapa , lista);

    gerarMatriz(atoi(vertices), graf);

    char aux[20];
    while(fgets(aux, 19, arq) != NULL){ //lendo o restante do arquivo até ele ser NULL :: fgets recebe o nome do auxiliar que vai receber a str, o tamanho dessa str, e de que arquivo

        int aux1, aux2;    //criando variáveis para colocar os valores que representam o indice do que está na lista

        for(int i = 0; i < sizeof(lista); i++){ //percorrendo a lista com os vertices
            if(aux[0] == lista[i]){ //verificando se o aux[0], no caso o primeiro caractere da linha, é igual a algum da lista
                aux1 = i; //e pego o seu indice
            }
            if(aux[1] == lista[i]){ //verificando se o aux[1], no caso o segundo caractere da linha, é igual a algum da lista
                aux2 = i;
            }            
        }
        inserirMatriz(aux1, aux2, graf);     
    }
    fclose(arq);
    imprimirMatriz(graf->vertices, graf);
}
void inserirMatriz(int aux1, int aux2, grafo *graf){

    for(int i = 0; i < graf->vertices; i++){
        for(int j = 0; j < graf->vertices; j++){
            if(i == aux1 && j == aux2){ //Comparando para ver se o i é igual o valor que está em aux
                graf->matriz[i][j] = 1;
            }
            if(j == aux1 && i == aux2){ //o inverso
                graf->matriz[i][j] = 1;
            }
        }
    }
    return;
}

fila* push(fila *fila,char v){
    struct fila *aux = fila;
    if(aux == NULL){
        struct fila *novo = malloc(sizeof(fila));
        novo->vertice = v;
        novo->prox = NULL;
        return novo;
    }
    else{
        struct fila *novo = malloc(sizeof(fila));
        novo->vertice = v;
        novo->prox = fila;
        return novo;
    }
}
fila* pop(fila *fila){
    if(fila != NULL){
        char v = fila->vertice;
        if(fila->prox != NULL){
            fila = fila->prox;
        }
        else{
            fila = NULL;
        }
    return fila;
    }
}
void buscaLargura(grafo *graf, char origem){
    fila *f = NULL; //inicializado filas com NULL
    fila *adjacentes = NULL;
    int tam = graf->vertices;
    int visitado[tam]; 
    for(int i = 0;i < graf->vertices; i++){ //inicializando lista de visitados
        visitado[i] = 0; 
    }

    for(int i = 0; i < graf->vertices; i++){ //busca início
        if(origem == graf->mapa[i]){
            f = push(f, graf->mapa[i]);//enfileirando origem graf->mapa[i]
            visitado[i] = 1; //visitado[i] = 1; 
            break;            
        }
    }    


    while(f != NULL){  //<-------
        char nomeVertice = f->vertice;
        f = pop(f); //pop
        for(int i = 0; i < graf->vertices; i++){ //busca o caractere da lista
            if(nomeVertice == graf->mapa[i]){ 
                // busca adjacentes----------------------------------------
                for(int j = 0; j < graf->vertices ; j++){
                    if(graf->matriz[i][j] == 1 && j != i ){                        

                        if(visitado[j] == 0){
                            adjacentes = push(adjacentes, graf->mapa[j]);
                        }                                                    
                    }
                }
            }
        }         
        while(adjacentes != NULL){ //o vetor de não visitados não estiver vazio
            char adjVertice = adjacentes->vertice;
            adjacentes = pop(adjacentes);
            for(int i = 0; i < graf->vertices; i++){ //busca vertice
                if(adjVertice == graf->mapa[i]){
                    if(visitado[i] == 0){
                        f = push(f,graf->mapa[i]);//enfileirando adjvert
                        printf(" -> %c", adjVertice);
                        visitado[i] = 1; //visitado[i] = 1;
                    }                    
                }
            }            
        }
    }
    printf("\n");
}