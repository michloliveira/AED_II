#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    no* raiz;
    no* aux;
    raiz = NULL;
    while(1==1){
        aux = NULL;
        int opcao;
        scanf("%d",&opcao);
        switch(opcao){
            int valor;
            case 1:
                scanf("%d",&valor);
                raiz = inserir(raiz,valor);
                break;
            case 2:
                preOrder(raiz);
                break;
            case 3:
                inOrder(raiz);
                break;
            case 4:
                posOrder(raiz);
                break;
            case 5:
                printf("[%d]",altura(raiz));
                break;
            case 6:
                printf("[%d]",maiorElemento(raiz));
                break;
            case 7:
                printf("[%d]",menorElemento(raiz));
                break;
            case 8:
                scanf("%d",&valor);
                remover(raiz,aux,valor);
                break;
            case 9:
                scanf("%d",&valor);
                sucessor(raiz,valor,-1);
                break;
            case 10:
                scanf("%d",&valor);
                antecessor(raiz,valor,-1);
                break;
            case 99:
                exit(0);
        }
    }
}
    
    
