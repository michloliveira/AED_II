#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

no* inserir(no* r,int valor){
    if(r == NULL){
        no* novo = (no*)malloc(sizeof(no));
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
    if(r!=NULL){
        printf("[%d]",r->valor);
        preOrder(r->esq);
        preOrder(r->dir);
    }
}
void inOrder(no* r){
    if(r!=NULL){
        inOrder(r->esq);
        printf("[%d]",r->valor);
        inOrder(r->dir);
    }
}
void posOrder(no* r){
    if(r!=NULL){
        posOrder(r->esq);
        posOrder(r->dir);
        printf("[%d]",r->valor);
    }
}
int maiorElemento(no* r){
    if(r!=NULL){
        if(r->dir!=NULL){
            maiorElemento(r->dir);
        }
        else{
            return r->valor;
        }
    }
}
int menorElemento(no* r){
    if(r!=NULL){
        if(r->esq!=NULL){
            menorElemento(r->esq);
        }
        else{
            return r->valor;
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
    if(r == NULL){
        return 0;
    }
    else{
        return 1 + max(altura(r->esq),altura(r->dir));
    }
}

void remover(no* r,no* aux,int valor){
    if(r!= NULL){
        if(valor == r->valor){
            //printf("[%d]",r->valor);
            remover_atual(aux,r);
        }
        if(valor > r->valor){
            aux = r;
            //printf("%d",aux->valor);
            remover(r->dir,aux,valor);
        }
        else{
            aux = r;
            //printf("%d",aux->valor);
            remover(r->esq,aux,valor);
        }
        
    }
}
void remover_atual(no* ant,no* atual){
    printf("\n");
    
    if(atual->esq != NULL && atual->dir != NULL){//remover com 2 filhos
        no* atualizaValor = atual;
        atual = atual->esq;
        while(atual->dir != NULL){
            ant = atual;
            atual = atual->dir;
        }
        atualizaValor->valor = atual->valor;
        remover_atual(ant,atual);
    }
    if(atual->esq == NULL && atual->dir == NULL){ //remover na folha
        if(ant->dir == atual){
            ant->dir = NULL;
            free(atual);
        }
        if(ant->esq == atual){
            ant->esq = NULL;
            free(atual);
        }
    }
    else{
        if(ant != NULL){
            if(ant->dir == atual){
                if(atual->dir == NULL){// se removido tem filho E ou D
                    ant->dir = atual->esq;
                    free(atual);
                }
                else{
                    ant->dir = atual->dir;
                    free(atual);
                }
            }
            else if(ant->esq == atual){
                if(atual->dir == NULL){
                    ant->esq = atual->esq;
                    free(atual);
                }
                else{
                    ant->esq = atual->dir;
                    free(atual);
                }
            }

        }
        else{//se o elemento e raiz e nao tem anterior
            if(atual->dir != NULL){
                atual = atual->dir;
            }
            else{
                atual = atual->esq;
            }
        }
    }
}
void antecessor(no* r,int valor,int aux){
    if(r!=NULL){
        if(valor == r->valor){
            if(r->esq != NULL){
                printf ("[%d]",maiorElemento(r->esq));
                //return maiorElemento(r->esq);
            }
            else{
                printf("[%d]",aux);
            }

        }//atualizando o auxiliar-----------------------
        if(r->valor < valor){// atualiza se o valor atual for MENOR que o pedido
            aux= r->valor;
        }//------------------------------------------
        //buscando.....
        if(valor > r->valor){
            antecessor(r->dir,valor,aux);
        }
        if(valor < r->valor){
            antecessor(r->esq,valor,aux);
        }
    }
}
void sucessor(no* r,int valor,int aux){
    if(r!=NULL){
        if(valor == r->valor){
            if(r->dir != NULL){
                printf("[%d]",menorElemento(r->dir));
            }
            else{
                printf("[%d]",aux);
            }

        
        }
        if(r->valor > valor){//atualiza SE Valor atual for MAIOR que o valor pedido
            aux = r->valor;
            //printf("aux = %d\n",aux);
        }
        if(valor > r->valor){
            sucessor(r->dir,valor,aux);
        }
        if(valor < r->valor){
            sucessor(r->esq,valor,aux);
        }
    }
}
