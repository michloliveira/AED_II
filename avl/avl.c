#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

arvore adicionar (int valor, arvore raiz, int *cresceu) {
	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_avl));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;
	  * cresceu = 1; 
		return novo;
	}
	if(valor > raiz->dado) {
		raiz->dir = adicionar(valor, raiz->dir, cresceu);
        if(*cresceu) {
			switch(raiz->fb) {
				case 0:
					raiz->fb = 1;
                    *cresceu = 1;
					break;
			    case -1:
					raiz->fb = 0;
					*cresceu = 0;
					break;
				case 1:
					*cresceu = 0;
					return rotacionar(raiz);
			}
		}

	} else {
	   raiz->esq = adicionar(valor,raiz->esq,cresceu);
	   if(*cresceu){
		   switch(raiz->fb){
			   case 0:
			   		raiz->fb = -1;
					*cresceu = 1;
					break;
			   case -1:
					*cresceu = 0;
					return rotacionar(raiz);
					break;
			   case 1:
			   		raiz->fb = 0;
					*cresceu = 0;
					break;

		   }
	   }
	}
	return raiz;
}

/*----------
Verifica o tipo de rotação que deve ser aplicado para reajustar a árvore
---*/
arvore rotacionar(arvore raiz) {
	if(raiz->fb > 0) {
		switch(raiz->dir->fb) {
			case 0:
			case 1:
				return rotacao_simples_esquerda(raiz);
			case -1:
				return rotacao_dupla_esquerda(raiz);					
			} 
	} else {
		switch(raiz->esq->fb){
			case 0:
			case -1:
				return rotacao_simples_direita(raiz);
			case 1:
				return rotacao_dupla_direita(raiz);
		}
	}
}

arvore remover (int valor, arvore raiz,int *diminuiu) {
	if(raiz == NULL){
		return NULL;
	}
	if(raiz->dado == valor){
		if(raiz->dir == NULL && raiz->esq == NULL){ //remover na folha
			*diminuiu = 1;
			free(raiz);
			return NULL;
		}
		else if(raiz->dir != NULL  && raiz->esq != NULL){//remover com 2 filhos
			raiz->dado = maior_elemento(raiz->esq);//atualiza valor atual com maior dado a esquerda
			raiz->esq = remover(raiz->dado,raiz->esq,diminuiu);
			if(*diminuiu){
				switch(raiz->fb){
					case 0:
						raiz->fb = 1;
						*diminuiu = 0;
						break;
					case -1:
						raiz->fb = 0;
						*diminuiu = 1;
						break;
					case 1:
						raiz->fb = 2;
						if(raiz->dir->fb == 0){
							*diminuiu = 0;
						}
						else{
							*diminuiu = 1;
						}
						return rotacionar(raiz);
						break;
				}
			}
			return raiz;
		}
		else{//remover com 1 filho
			if(raiz->dir != NULL){
				*diminuiu = 1;
				return raiz->dir;
			}
			else{
				*diminuiu = 1;
				return raiz->esq;
			}
		}
	}
	if(valor > raiz->dado) {
		raiz->dir = remover(valor, raiz->dir,diminuiu);
		if(*diminuiu){//Diminuiu!, atualiza o fator de balanço do nó atual
			switch(raiz->fb){
				case 1:
					raiz->fb = 0;
					*diminuiu = 1;
					break;
				case 0:
					raiz->fb = -1;
					*diminuiu = 0;
					break;
				case -1:
					raiz->fb = -2; // dispara a rotação
					if(raiz->esq->fb == 0){
						*diminuiu = 0;
					}
					else{
						*diminuiu = 1;
					}
					return rotacionar(raiz);
					break;
			}
		}
	} else {
		raiz->esq = remover(valor, raiz->esq,diminuiu);
		if(*diminuiu){
			switch(raiz->fb){
				case 1:
					raiz->fb = 2;
					if(raiz->dir->fb == 0){
						*diminuiu = 0;
					}
					else{
						*diminuiu = 1;
					}
					return rotacionar(raiz);
					break;
				case 0:
					raiz->fb = 1;
					*diminuiu = 0;
					break;
				case -1:
					raiz->fb = 0;
					*diminuiu = 1;
					break;
			}
		}
	}
	return raiz;

}

/*-------
rotação simples esquerda 
      p
     / \
    t1  u
       / \
      t2 t3

     =>

      u
     / \
    p  t3
   / \
  t1 t2

-------*/
arvore rotacao_simples_esquerda(arvore raiz) {
	arvore p, u, t1, t2, t3;
    //inicializa os ponteiros
	p = raiz;
	u = raiz->dir;
    t1 = p->esq;
    //t2 e t3 não estão sendo modificados. 
    //só estão aqui por questões didáticas
    t2 = u->esq;
    t3 = u->dir;

    //Atualiza os ponteiros
	u->esq = p;
	p->dir = t2;
    
    //Atualiza os fatores de balanço de acordo com o fb de u
    //Esses valores vieram dos cálculos demonstrados na aula
	if(u->fb == 1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = 1;
		u->fb = -1;
	}	
    
    //Retorna a raiz da sub-árvore resultante, ou seja "u".
	return u;
}

arvore rotacao_dupla_esquerda(arvore raiz) {
	arvore p,u,v;
	p = raiz;
	u = p->dir;
	v = u->esq;
	u->esq = v->dir;
	v->dir = u;
	p->dir = v->esq;
	v->esq = p;
	if(v->fb == 0){ //todos possuem subArvore
		p->fb = 0;		   
		u->fb = 0;	
		v->fb = 0;	
	}
	else if(v->fb == 1){ // subArvore dir de p vazia
		p->fb = -1;
		u->fb = 0;
		v->fb = 0;
	}
	else{ //subArvore esq de u vazia
		u->fb = 1;
		p->fb = 0;
		v->fb = 0;
	}
	return v;
}

arvore rotacao_simples_direita(arvore raiz) {
	arvore p,u,t1 ,t2,t3;
	//inicializar os ponteiros
	p = raiz;
	u = raiz->esq;
	t1 = p->dir;
	t2 = u->dir;
	t3 = u->esq;
	//atualiza ponteiros
	u->dir = p;
	p->esq = t2;
	if(u->fb == -1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = -1;
		u->fb = 1;
	}	

	return u;
}
arvore rotacao_dupla_direita(arvore raiz) {
	arvore p,u,v;
	p = raiz;
	u = p->esq;
	v = u->dir;
	u->dir = v->esq;
	v->esq = u;
	p->esq = v->dir;
	v->dir = p;
	if(v->fb == 0){
		u->fb = 0;
		p->fb = 0;
		v->fb = 0;
	}
	else if(v->fb == 1){
		u->fb = -1;
		v->fb = 0;
		p->fb = 0;
	}
	else{
		p->fb = 1;
		v->fb = 0;
		u->fb = 0;
	}
	return v;
}

/*---
Imprime a árvore ,incluindo também o fator de balanço.
---*/
void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

/*---
Auxiliar de imprimir
---*/
void imprimir_elemento(arvore raiz) {
	printf("%d [%d]", raiz->dado, raiz->fb);
}
int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return menor_elemento(raiz->esq);
}

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

