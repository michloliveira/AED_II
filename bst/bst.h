#ifndef BST_H
#define BST_H

typedef struct no {
    int valor;
    struct no* dir;
    struct no* esq;
}no;

no* inserir(no* r, int valor);
void preorder(no* r);
void inorder(no* r);
void posorder(no* r);
no* maior(no* r);
no* menor(no* r);
int quantidade_elementos(no* r);
int existe(no* r,int valor);
int max(int a, int b);
int altura(no* raiz);
no* predecessor(no* r,int valor);
no* sucessor(no* r,int valor);
no* remover(no* r,int valor);



#endif
