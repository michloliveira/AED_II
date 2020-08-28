#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

no* inserir(no* r,int chave){
    if(r == NULL){
        no* novo =(no*)malloc(sizeof(no));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->chave = chave;
        return novo;
    }
    if(chave > r->chave){
        r->dir = inserir(r->dir,chave);
    }
    else{
        r->esq = inserir(r->esq,chave);
    }
    return r;
}
void preorder(no* r){
    if(r != NULL){
        printf("[%d]",r->chave);
        preorder(r->esq);
        preorder(r->dir);
    }
}
void inorder(no* r){
    if(r != NULL){
        inorder(r->esq);
        printf("[%d]",r->chave);
        inorder(r->dir);
    }
}
void posorder(no* r){
    if(r != NULL){
        posorder(r->esq);
        posorder(r->dir);
        printf("[%d]",r->chave);
    }
}
no* maior(no* r){
    if(r != NULL){
        if(r->dir != NULL){
            maior(r->dir);
        }
        else{
            return r;
        }
    }
}
no* menor(no* r){
    if(r != NULL){
        if(r->esq != NULL){
            menor(r->esq);
        }
        else{
            return r;
        }
    }
}
int quantidade_elementos(no* r){
    if(r != NULL){
        int contadorEsquerdo = quantidade_elementos(r->esq);
        int contadorDireito = quantidade_elementos(r->dir); 
        return 1 + contadorDireito + contadorEsquerdo;
    }
    else{
        return 0;
    }
}
int existe(no* r, int chave){
    if(r != NULL){
        if(chave == r->chave){
            return 1;
        }
        else if(chave < r->chave && r->esq != NULL){
            existe(r->esq,chave);
        }
        else if(chave > r->chave && r->dir != NULL){
            existe(r->dir,chave);
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
no* predecessor(no* r,int chave){
    no* aux = NULL;
    no* raiz = r;
    if(raiz != NULL){
        while(chave != raiz->chave){ //buscando...
            if(chave > raiz->chave){ 
                aux = raiz; // atuliza aux se raiz->chave for menor que o chave
                raiz = raiz->dir;
            }
            else{
                raiz = raiz->esq;
            }
        }

        if(raiz->esq != NULL){
            return maior(raiz->esq);
        }
        else{
            return aux;
        }   
    }
}
no* sucessor(no* r,int chave){
    no* aux = NULL;
    no* raiz = r;
    if(raiz != NULL){
        while(chave != raiz->chave){ //buscando...
            if(chave > raiz->chave){ 
                raiz = raiz->dir;
            }
            else{
                aux = raiz; //autualiza aux se r->chave for
                raiz = raiz->esq;
            }
        }

        if(raiz->dir != NULL){
            return menor(raiz->dir);
        }
        else{
            return aux;
        }   
    }
}
no* remover(no* r,int chave){
    if(r != NULL){
        if(existe(r,chave) == 0){// verificando se o chave existe
            return r;
        }
        no* ant = NULL;// instanciando um anterior
        no* atual = r; //instanciando um no auxiliar
        no* aux = NULL; //instanciando  um no aux;
        while(chave != atual->chave){ //---Buscando...
            if(chave > atual->chave){
                ant = atual;
                atual = atual->dir;
            }
            else{
                ant = atual;
                atual = atual->esq;
            }
        }
        //--------------------------------------------------------------
        if(atual->dir == NULL && atual->esq == NULL){ //caso 1 ,remover na folha
            //printf("entrou caso 1\n");
            if(ant != NULL){
                if(ant->dir == atual){
                    ant->dir = NULL;
                    free(atual);
                    return r; //retorna a raiz
                }
                else{
                    //printf("removeu!\n");
                    ant->esq = NULL;
                    free(atual);
                    return r; //retorna raiz
                }
            }else{
                free(atual);
                return NULL;
            }
        }
        //----------------------------------------------------------------------
        if(atual->dir != NULL && atual->esq != NULL){ //caso 3 remover com 2 filhos
            aux = menor(atual->dir); //atualiza chave atual com menor chave a direita
            atual->chave = aux->chave;
            atual->dir = remover(atual->dir,atual->chave);
            return r;
        }
        //----------------------------------------------------------------------
        else{ //caso 2 , remover com 1 filho
            if(ant != NULL){
                if(ant->dir == atual){
                    if(atual->dir != NULL){ //anterior dir aponta para atual dir
                        ant->dir = atual->dir;
                        free(atual);
                        return r;
                    }
                    else{ //anterior dir aponta para atual esq
                        ant->dir = atual->esq;
                        free(atual);
                        return r;
                    }
                }//ant-> esq == atual
                else{
                    if(atual->dir != NULL){ // anterior esq aponta para o atual dir
                        ant->esq = atual->dir;
                        free(atual);
                        return r;
                    }
                    else{
                        ant->esq = atual->esq; // anterior esq aponta para o atual esq
                        free(atual);
                        return r;
                    }
                }
            }
            else{
                if(atual->dir != NULL){
                    r = atual->dir;
                    free(atual);
                    return r;
                }
                else{
                    r = atual->esq;
                    free(atual);
                    return r;
                }
            }
        }
    }
    return r;
}
