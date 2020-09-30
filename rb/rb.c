#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;

/*
Inicializa a árvore vazia com a raiz = null e inicializa o nó nulo duplo preto que será utilizado no método remover.
*/
void inicializar(arvore *raiz) {
	*raiz = NULL;
	no_null = (arvore) malloc(sizeof(struct no_bst));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
}

/* Adiciona um novo elemento na árvore.
Parâmetros:
    valor   - elemento a ser adicionado
    raiz    - árvore onde o elemento será adicionado. 
            Observe que este parâmetro é um ponteiro de ponteiro
*/
void adicionar (int valor, arvore *raiz) {
	arvore posicao, pai, novo;
    //utiliza-se *raiz, por ser um ponteiro de ponteiro
	posicao = *raiz;
	pai = NULL;

	/*navega na árvore até encontrar a posição vaga apropriada para o elemento,
		nesta "descida" é necessário manter o ponteiro para o pai, pois após encontrar 
		a posição vaga (NULL) não seria possível navegar para o pai com o ponteiro posicao->pai */
	while(posicao != NULL) {
			pai = posicao;
			if(valor > posicao->dado) 
					posicao = posicao->dir;
			else 
					posicao = posicao->esq;
	}

    //Após achar a posição, inicializa o novo elemento
	novo = (arvore) malloc(sizeof(struct no_bst));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

    //Atualiza a raiz da árvore, caso esteja inserindo o primeiro elemento
    //Observe novamente o uso do ponteiro de ponteiro
	if(eh_raiz(novo))	
			*raiz = novo;
	else {
        //Se não for a raiz, é preciso realizar a ligação do pai(direita ou esquerda) com o novo elemento
		if(valor > pai->dado)
			pai->dir = novo;
		else
			pai->esq = novo;
	}

    //Após inserir, verifica e ajusta a árvore resultante
	ajustar(raiz, novo);
}


/* Verifica se a árvore está obedecendo todas as regras da RB e aplica as correções necessárias após a inserção.
Parâmetros:
    raiz - raiz (absoluta) da árvore
    elemento - nó recentemente inserido que pode ter causado o desajuste da árvore
*/
void ajustar(arvore *raiz, arvore elemento){
    //A árvore está desajustada se tanto o elemento quanto o seu pai estiverem com a cor vermelha
    //Utilizamos um while para continuar a verificação até chegar a raiz, quando necessário
	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
			//caso 1: Cor do tio é vermelha, desce o preto do avô
			if(cor(tio(elemento)) == VERMELHO) {
				tio(elemento)->cor = PRETO;
				elemento->pai->cor = PRETO;
				elemento->pai->pai->cor = VERMELHO;
				//Continua a verificação a partir do avô, que mudou para vermelho e pode ter 
				//gerado uma sequência vermelho-vermelho				
				elemento = elemento->pai->pai;
				continue;
			} 
			//caso 2a: rotacao simples direita
			if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
					rotacao_simples_direita(raiz, elemento->pai->pai);
					elemento->pai->cor = PRETO;
					elemento->pai->dir->cor = VERMELHO;
					continue;
			}
			//caso 2b: rotacao simples esquerda
			if(!eh_filho_esquerdo(elemento)&& !eh_filho_esquerdo(elemento->pai)) {
				rotacao_simples_esquerda(raiz,elemento->pai->pai);
				elemento->pai->cor = PRETO;
				elemento->pai->esq->cor = VERMELHO;
				continue;
			}
			//caso 3a: rotacao dupla direita
			if(!eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai) && cor(tio(elemento)) == PRETO){//se o filho é filho esquerdo && o pai é filho direito
				rotacao_dupla_direita(raiz,elemento->pai->pai);
				continue;
			}
			//caso 3b: rotacao dupla esquerda
			if(eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai) && cor(tio(elemento)) == PRETO){
				rotacao_dupla_esquerda(raiz,elemento->pai->pai);
				continue;
			}

	}
    //Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta
	(*raiz)->cor = PRETO;
}

/* Realiza a rotacao simples direita
Antes da rotacao: 
cor(p) = Preto
cor(u) = cor(v) = Vermelho

       p             u
      / \           / \
     u  t2   =>    v   p
    / \               / \
   v  t1             t1 t2

Após aa rotacao: 
cor(u) = Preto
cor(v) = cor(p) = Vermelho
*/
void rotacao_simples_direita(arvore *raiz, arvore pivo){
			arvore u, t1;
			u = pivo->esq;
            t1 = u->dir;

            /*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito*/
			int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			
			//Atualização dos ponteiros
			pivo->esq = t1;
            if(t1 != NULL)
				t1->pai = pivo;

			u->dir = pivo;
            
			u->pai = pivo->pai;
			pivo->pai = u;

			

			//mudança das cores
    		pivo->cor = VERMELHO;
			u->cor = PRETO;
            //Se não existir árvore acima de u, u passa a ser a raiz da árvore
			if(eh_raiz(u))
				*raiz = u;
			else {
              //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotacao
					if(posicao_pivo_esq)
							u->pai->esq = u;
					else
							u->pai->dir = u;
			}
}
/* rotacao simples esquerda
	   p			u
	  / \		   / \
	 t2  u    =>  p	  v
	 	/ \      / \
	   t1  v    t2 t1
*/
void rotacao_simples_esquerda(arvore *raiz, arvore pivo) {
	arvore u, t1;
	u = pivo->dir;
	t1= u->esq;
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
	//atualização dos ponteiros
	pivo->dir = t1;
	if(t1 != NULL){
		t1->pai = pivo;
	}
	u->esq = pivo;
	u->pai = pivo->pai;
	pivo->pai = u;
	//mudança de cor
	pivo->cor = VERMELHO;
	u->cor = PRETO;
	if(eh_raiz(u)){
		*raiz = u;
	}
	else{
		if(posicao_pivo_esq){
			u->pai->esq = u;
		}
		else{
			u->pai->dir = u;
		}
	}
	printf("rotacao_simples_esquerda\n");
}
/*
	p					p					v
   / \				   / \				   / \
  t1  u				  t1  v				  p    u 
     / \		=> 	     / \ 		=>   / \  / \
	v   t4				t2  u			t1 t2 t3 t4
   / \					   / \
  t2 t3					  t3  t4
*/
void rotacao_dupla_direita(arvore *raiz, arvore pivo){
	arvore v,u,t2,t3;
	u = pivo->esq;
	v = u->dir;
	t2 = v->esq;
	t3 = v->dir;
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
	//rotação simples direita
	u->dir = t2;
	v->esq = u;
	pivo->esq = v;
	//rotação simples esquerda
	pivo->esq = t3;
	v->dir = pivo;
	v->esq = u;
	//atualiza pai

	if(t2!= NULL){
		t2->pai = u;
	}
	if(t3!= NULL){
		t3->pai = pivo; //////
	}
	u->pai = v;
	v->pai = pivo->pai;
	//mudar as cores
	pivo->cor = VERMELHO;
	v->cor = PRETO;
	if(eh_raiz(pivo)){
		*raiz = v;
	}
	else{
		if(posicao_pivo_esq){
			pivo->pai->esq = v;
		}
		else{
			pivo->pai-> dir = v;
		}
	}
	pivo->pai = v;

}
void rotacao_dupla_esquerda(arvore *raiz, arvore pivo){
	arvore v,u,t2,t3;
	u = pivo->dir;
	v = u->esq;
	t2 = v->esq;
	t3 = v->dir;
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
	//rotação simples esquerda
	u->esq = t3;
	v->dir = u;
	pivo->dir = v;
	//rotação simples direita
	pivo->dir = t2;
	v->esq = pivo;
	v->dir = u;
	//atualiza pai

	if(t2!= NULL){
		t2->pai = pivo;
	}
	if(t3!= NULL){
		t3->pai = u; ////////
	}
	u->pai = v;
	v->pai = pivo->pai;
	//mudar as cores
	pivo->cor = VERMELHO;
	v->cor = PRETO;
	if(eh_raiz(pivo)){
		*raiz = v;
	}
	else{
		if(posicao_pivo_esq){
			pivo->pai->esq = v;
		}
		else{
			pivo->pai-> dir = v;
		}
	}
	pivo->pai = v;

}

/*Retorna a cor de um nó. Observe que, por definição, o null é preto*/
enum cor cor(arvore elemento) {
	enum cor c;
	if(elemento==NULL || elemento->cor == PRETO)
		c = PRETO;
	else
		c = VERMELHO;
	return c;
}
/*Verifica se um nó é a raiz da árvore*/
int eh_raiz(arvore elemento) {
	return (elemento->pai == NULL);
}
/*Verifica se um nó é filho esquerdo*/
int eh_filho_esquerdo(arvore elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

arvore tio(arvore elemento) {
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento) {
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}


void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
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

void imprimir_elemento(arvore raiz) {
	switch(raiz->cor){
		case PRETO:
			printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
			break;
	}
}

void remover (int valor, arvore *raiz) {
	arvore posicao;
	posicao = *raiz;

	while(posicao != NULL) {
		if(valor == posicao->dado) {
				//O elemento não possui filhos
				if(posicao->esq == NULL && posicao->dir == NULL) {
					//Remover raiz sem filhos					
					if(eh_raiz(posicao)) {
						*raiz = NULL;
						break;
					}
					//Remover elemento que não possui filhos e não é raiz
					//Se for vermelho, apenas remove atualizando o ponteiro 
					//correspondente do pai
					if(posicao->cor == VERMELHO) {
							if(eh_filho_esquerdo(posicao))
								posicao->pai->esq = NULL;
							else
								posicao->pai->dir = NULL;
							break;
					} else {
							//Se o elemento for preto, substitui pelo duplo preto e depois ajusta a árvore
							no_null->pai = posicao->pai;
							//no_null->cor = DUPLO_PRETO;
							if(eh_filho_esquerdo(posicao)){
								posicao->pai->esq = no_null;
							}
							else{
								posicao->pai->dir = no_null;
								
							}
							reajustar(raiz, no_null);
							break;
					}
					break;
				}

				//O elemento possui apenas um filho (direito)
				if(posicao->esq == NULL) {
					posicao->dir->cor = PRETO;
					if(eh_raiz(posicao)) {
						*raiz = posicao->dir;
					} else {
						if(eh_filho_esquerdo(posicao)) {
							posicao->pai->esq = posicao->dir;
						} else {
							posicao->pai->dir = posicao->dir;
						}
					}
					break;
				}


				//O elemento possui apenas um filho (esquerdo)
				if(posicao->dir == NULL) {
					posicao->esq->cor = PRETO;
					if(eh_raiz(posicao)) {
						*raiz = posicao->esq;
					} else {
						if(eh_filho_esquerdo(posicao)) {
							posicao->pai->esq = posicao->esq;
						} else {
							posicao->pai->dir = posicao->esq;
						}
					}
					break;
				}

				//elemento possui dois filhos 
				posicao->dado = maior_elemento(posicao->esq);
				remover(posicao->dado, &(posicao->esq));
		}	
		if(valor > posicao->dado){
				posicao = posicao->dir;
		}
		else{
				posicao = posicao->esq;
		}
	}
}

/*Realiza a correção da árvore após a remoção de um elemento preto que não possui filhos, ou seja, elimina o nó null o duplo-preto.*/

void reajustar(arvore *raiz, arvore elemento){
//	cor(irmao(elemento)->dir), cor(irmao(elemento)->esq));
	//caso 1
	if(eh_raiz(elemento)) {
		printf("caso 1\n");
		elemento->cor = PRETO;
		return;
	}
	//caso 2
	if(cor(elemento->pai) == PRETO &&
		 cor(irmao(elemento)) == VERMELHO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO ) {
			 printf("CASO 2\n");
				//printf("cor %d\n",cor(irmao(elemento)));
                //Verifica se é o caso 2 esquerdo ou direito
				if(eh_filho_esquerdo(elemento)){
						rotacao_simples_esquerda(raiz, elemento->pai);
				}
				else{
					rotacao_simples_direita(raiz, elemento->pai);	
				}
				elemento->pai->pai->cor = PRETO;
				elemento->pai->cor = VERMELHO;
                //Atenção à chamada recursiva do reajustar.
                //O caso 2 não remove o duplo-preto
                reajustar(raiz, elemento);
				return;
	}

	//caso 3
	if(cor(elemento->pai) == PRETO &&
	 cor(irmao(elemento)) == PRETO && 
	 cor(irmao(elemento)->dir) == PRETO &&
	 cor(irmao(elemento)->esq) == PRETO ) {
		 printf("CASO 3\n");
			//printf("cor %d\n",cor(irmao(elemento)));
			//imprimir(elemento);
		 if(eh_filho_esquerdo(elemento)){
			 elemento->pai->dir->cor = VERMELHO;
			 elemento->pai->cor = DUPLO_PRETO;
			 elemento->cor = PRETO;
		 }
		 else{
			 elemento->pai->esq->cor = VERMELHO;
			 elemento->pai->cor = DUPLO_PRETO;
			 elemento->cor = PRETO;
		 }

		reajustar(raiz,elemento->pai);
		return;
	}	

	//caso 4
	if(cor(elemento->pai) == VERMELHO &&
	cor(irmao(elemento)) == PRETO &&
	cor(irmao(elemento)->dir) == PRETO &&
	cor(irmao(elemento)->esq) == PRETO){
		printf("CASO 4\n");
		if(eh_filho_esquerdo(elemento)){
			elemento->pai->dir->cor = VERMELHO;
			elemento->pai->cor = PRETO;
			retira_duplo_preto(raiz,elemento);
		}
		else{
			elemento->pai->esq->cor = VERMELHO;
			elemento->pai->cor = PRETO;
			retira_duplo_preto(raiz,elemento);
		}
		return;
	}
    //Casos 5 e 6 ficam mais fáceis separando o esquerdo do direito
	//caso 5a
	if(cor(elemento->pai->dir) == PRETO &&
	cor(irmao(elemento)->dir) == PRETO &&
	cor(irmao(elemento)->esq) == VERMELHO){
		printf("CASO 5a\n");
		arvore p,s,x,y;
		//inicializar
		p = elemento->pai;
		s = elemento->pai->dir;
		x = elemento->pai->dir->esq;
		y = elemento->pai->dir->dir;
		//rotacionar
		x->dir = s;
		p->dir = x;
		//set pai
		x->pai = p; ////////////!!!!!!!!
		s->pai = x;
		//recolorir
		x->cor = PRETO;
		s->cor = VERMELHO;

		reajustar(raiz, elemento);
		return;
	}

	//caso 5b
	if(cor(elemento->pai->esq) == PRETO &&
	cor(irmao(elemento)->dir) == VERMELHO &&
	cor(irmao(elemento)->esq) == PRETO){
		printf("CASO 5B\n");
		arvore p,s,x;
		//inicializar
		p = elemento->pai;
		s = elemento->pai->esq;
		x = elemento->pai->esq->dir;
		//rotacionar
		s->dir = x->esq; //<----------
		p->esq = x;
		x->esq = s;
		//set pai
		x->pai = p;
		s->pai = x;
		//recolorir
		x->cor = PRETO;
		s->cor = VERMELHO;

		reajustar(raiz, elemento);
		return;
	}

	//caso 6a
	if(cor(elemento->pai->dir) == PRETO &&
	cor(irmao(elemento)->dir) == VERMELHO){
		printf("CASO6A\n");
		arvore p,s,x,y;
		//inicialização
		p = elemento->pai;
		s = elemento->pai->dir;
		x = elemento->pai->dir->esq;
		y = elemento->pai->dir->dir;
		int posicao_pivo_esq = eh_filho_esquerdo(elemento->pai);
		//rotação
		p->dir = x;
		s->esq = p;
		//set cor
		s->cor = cor(p);
		y->cor = PRETO;
		p->cor = PRETO;
		//set pai
		if(x != NULL){
			x->pai = p;
		}
		if(eh_raiz(elemento->pai)){
			*raiz = s;

		}
		else{
			if(posicao_pivo_esq){
				p->pai->esq = s;
			}
			else{
				p->pai->dir = s;
			}
		}
		s->pai = p->pai;
		p->pai = s;
		y->pai = s;

		retira_duplo_preto(raiz,elemento);
		return;
	}

	//caso 6b
	if(cor(elemento->pai->esq) == PRETO &&
	cor(irmao(elemento)->esq) == VERMELHO){
		printf("CASO6A\n");
		arvore p,s,x,y;
		//inicializando
		p = elemento->pai;
		s = elemento->pai->esq;
		x = elemento->pai->esq->dir;
		y = elemento->pai->esq->esq;
		int posicao_pivo_esq = eh_filho_esquerdo(elemento->pai);
		//rotacionando
		p->esq = x;
		s->dir = p;
		//set cor
		s->cor = cor(p);
		y->cor = PRETO;
		p->cor = PRETO;
		//set pai
		if(x != NULL){
			x->pai = p;
		}
		if(eh_raiz(elemento->pai)){
			*raiz = s;

		}
		else{
			if(posicao_pivo_esq){
				p->pai->esq = s;
			}
			else{
				p->pai->dir = s;
			}
		}
		s->pai = p->pai;
		p->pai = s;
		y->pai = s;
		retira_duplo_preto(raiz,elemento);
		return;
	}
}

void retira_duplo_preto(arvore *raiz, arvore elemento) {
	printf("retira duplo preto\n");
			if(elemento == no_null)
				if(eh_filho_esquerdo(elemento))
						elemento->pai->esq = NULL;
				else
						elemento->pai->dir = NULL;
			else
				elemento->cor = PRETO;
}

