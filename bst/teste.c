#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    no* raiz;
    raiz = NULL;
    
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
            case 5:
                printf("[%d]",altura(raiz));
                break;
            case 6:
                maiorElemento(raiz);
                break;
            case 7:
                menorElemento(raiz);
                break;
            case 8:
            case 9:
            case 10:
            case 99:
                exit(0);
        }
    }
}
    
    
