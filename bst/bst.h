#ifndef BST_H
#define BST_H

typedef struct no {
    int chave;
    struct no* dir;
    struct no* esq;
}no;

no* inserir(no* r, int chave);
void preorder(no* r);
void inorder(no* r);
void posorder(no* r);
no* maior(no* r);
no* menor(no* r);
int quantidade_elementos(no* r);
int existe(no* r,int chave);
int max(int a, int b);
int altura(no* raiz);
no* predecessor(no* r,int chave);
no* sucessor(no* r,int chave);
no* remover(no* r,int chave);



#endif
