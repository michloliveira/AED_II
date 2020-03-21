#ifndef BST_H
#define BST_H

typedef struct no{
    int valor;
    struct no* dir;
    struct no* esq;
}no;

no* inserir(no* r,int valor);
void preOrder(no* r);
void inOrder(no* r);
void posOrder(no* r);
int maiorElemento(no* r);
int menorElemento(no* r);
int max(int a, int b);
int altura(no* r);
void remover(no* r,no* aux,int valor);
void remover_atual(no* ant,no* atual);
void antecessor(no* r,int valor,int aux);
void sucessor(no* r,int valor,int aux);


#endif
