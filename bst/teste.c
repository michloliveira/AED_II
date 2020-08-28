#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    no* raiz = NULL;
    while(1==1){
        int opcao;
        no* retorno;
        scanf("%d",&opcao);
        switch(opcao){
            int valor;
            case 1:
                scanf("%d",&valor);
                raiz = inserir(raiz,valor);
                break;
            case 2:
                preorder(raiz);
                break;
            case 3:
                inorder(raiz);
                break;
            case 4:
                posorder(raiz);
                break;
            case 5:
                scanf("%d",&valor); 
                raiz = remover(raiz,valor);
                break;
            case 6:
                retorno = maior(raiz);
                printf("[%d]",retorno->valor);
                break;
            case 7:
                retorno = menor(raiz);
                printf("[%d]",retorno->valor);
                break;
            case 8:
                printf("[%d]",altura(raiz));
                break;
            case 9:
                printf("[%d]",quantidade_elementos(raiz));
                break;
            case 10:
                scanf("%d",&valor);
                printf("[%d]",existe(raiz,valor));
                break;
            case 11:
                scanf("%d",&valor);
                retorno = predecessor(raiz,valor);
                printf("[%d]",retorno->valor);
                break;
            case 12:
                scanf("%d",&valor);
                retorno = sucessor(raiz,valor);
                printf("[%d]",retorno->valor);
                break;
            case 99:
                exit(0);
        }
    }
}
