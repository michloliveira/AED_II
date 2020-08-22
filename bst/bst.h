#ifndef BST_H
#define BST_H

typedef struct no {
    int valor;
    struct no* dir;
    struct no* esq;
}no;

no* inserir(no* r, int valor);
void preOrder(no* r);
void inOrder(no* r);
void posOrder(no* r);
int maiorElemento(no* r);
int menorElemento(no* r);
int quantidade(no* r,int contador);
int existeElemento(no* r,int valor);



#endif
