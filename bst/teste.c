#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    no* raiz = NULL;
    while(1==1){
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
            case 6:
                printf("[%d]",maiorElemento(raiz));
            case 99:
                exit(0);
        }
    }
}
