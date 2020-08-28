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
            int chave;
            case 1:
                scanf("%d",&chave);
                raiz = inserir(raiz,chave);
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
                scanf("%d",&chave); 
                raiz = remover(raiz,chave);
                break;
            case 6:
                retorno = maior(raiz);
                printf("[%d]",retorno->chave);
                break;
            case 7:
                retorno = menor(raiz);
                printf("[%d]",retorno->chave);
                break;
            case 8:
                printf("[%d]",altura(raiz));
                break;
            case 9:
                printf("[%d]",quantidade_elementos(raiz));
                break;
            case 10:
                scanf("%d",&chave);
                printf("[%d]",existe(raiz,chave));
                break;
            case 11:
                scanf("%d",&chave);
                retorno = predecessor(raiz,chave);
                printf("[%d]",retorno->chave);
                break;
            case 12:
                scanf("%d",&chave);
                retorno = sucessor(raiz,chave);
                printf("[%d]",retorno->chave);
                break;
            case 99:
                exit(0);
        }
    }
}
