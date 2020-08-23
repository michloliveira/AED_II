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
void predecessor(no* r,int aux,int valor){
    if(r != NULL){
        if(valor == r->valor){
            if(r->esq != NULL){
                printf("[%d",maiorElemento(r->esq));
            }
            else{
                if(aux != 0){
                    printf("[%d]",aux);
                }
            }

        }
        else{//buscando 
            if(valor > r->valor){ 
                aux = r->valor; // atuliza aux se r->valor for menor que o valor
                predecessor(r->dir,aux,valor);
            }
            else{
                predecessor(r->esq,aux,valor);
            }
        }
    }
}
void sucessor(no* r,int aux,int valor){
    if(r != NULL){
        if(valor == r->valor){
            if(r->dir != NULL){
                printf("[%d]",menorElemento(r->dir));
            }
            else{
                if(aux != 0){
                    printf("[%d]",aux);
                }
                
            }
        }
        else{
            if(valor > r->valor){
                sucessor(r->dir,aux,valor);
            }
            else{
                aux = r->valor; //autualiza aux se r->valor for maior valor
                sucessor(r->esq,aux,valor);
            }
        }
    }
}
no* remover(no* r,int valor){
    if(r != NULL){
        if(existeElemento(r,valor) == 0){// verificando se o valor existe
            return r;
        }
        no* ant = NULL;// instanciando um anterior
        no* atual = r; //instanciando um no auxiliar
        while(valor != atual->valor){ //---Buscando...
            if(valor > atual->valor){
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
            atual->valor = menorElemento(atual->dir); //atualiza valor atual com maior valor a direita
            atual->dir = remover(atual->dir,atual->valor);
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
