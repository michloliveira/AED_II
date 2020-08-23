#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

no* inserir(no* r,int valor){
    if(r == NULL){
        no* novo =(no*)malloc(sizeof(no));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->valor = valor;
        return novo;
    }
    if(valor > r->valor){
        r->dir = inserir(r->dir,valor);
    }
    else{
        r->esq = inserir(r->esq,valor);
    }
    return r;
}
void preOrder(no* r){
    if(r != NULL){
        printf("[%d]",r->valor);
        preOrder(r->esq);
        preOrder(r->dir);
    }
}
void inOrder(no* r){
    if(r != NULL){
        inOrder(r->esq);
        printf("[%d]",r->valor);
        inOrder(r->dir);
    }
}
void posOrder(no* r){
    if(r != NULL){
        posOrder(r->esq);
        posOrder(r->dir);
        printf("[%d]",r->valor);
    }
}
int maiorElemento(no* r){
    if(r != NULL){
        if(r->dir != NULL){
            maiorElemento(r->dir);
        }
        else{
            return r->valor;
        }
    }
}
int menorElemento(no* r){
    if(r != NULL){
        if(r->esq != NULL){
            menorElemento(r->esq);
        }
        else{
            return r->valor;
        }
    }
}
int quantidade(no* r,int contador){
    if(r != NULL){
        contador++;
        contador = quantidade(r->esq,contador); //contador recebe o calculo voltando
        contador = quantidade(r->dir,contador); 
        return contador;
    }
    else{
        return contador;
    }
}
int existeElemento(no* r, int valor){
    if(r != NULL){
        if(valor == r->valor){
            return 1;
        }
        else if(valor < r->valor && r->esq != NULL){
            existeElemento(r->esq,valor);
        }
        else if(valor > r->valor && r->dir != NULL){
            existeElemento(r->dir,valor);
        }
        else{
            return 0;
        }
    }
}
int max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

int altura(no* r){
    if(r != NULL){
        return 1 + max(altura(r->dir),altura(r->esq));
    }
    else{
        return 0;
    }
}
int predecessor(no* r,int aux,int valor){
    if(r != NULL){
        if(valor == r->valor){
            if(r->esq != NULL){
                return maiorElemento(r->esq);
            }
            else{
                return aux;
            }

        }
        else{//buscando 
            if(valor > r->valor){ 
                aux = r->valor; // atuliza auxiliar se r->valor for menor que o valor
                predecessor(r->dir,aux,valor);
            }
            else{
                predecessor(r->esq,aux,valor);
            }
        }
    }
}
