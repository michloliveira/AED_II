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
