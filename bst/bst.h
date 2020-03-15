#ifndef BST_H
#define BST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no* dir;
    struct no* esq;
}no;

no* inserir(no* r,int valor);
void preOrder(no* r);
void inOrder(no* r);
void posOrder(no* r);
void maiorElemento(no* r);
void menorElemento(no* r);
int max(int a, int b);
int altura(no* r);


#endif
