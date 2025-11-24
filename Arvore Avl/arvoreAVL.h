#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int chave;
    int altura;
    struct NO *esq;
    struct NO *dir;
} NO;

typedef NO* ArvAVL;

static int altura_no(NO *n){ return n ? n->altura : -1; }
static int max2(int a,int b){ return a>b?a:b; }
static int fator_balanceamento(NO *n){ return n ? altura_no(n->esq) - altura_no(n->dir) : 0; }
static void atualiza_altura(NO *n){ if(n) n->altura = 1 + max2(altura_no(n->esq), altura_no(n->dir)); }

/* rotações básicas */
static void rotacao_direita(ArvAVL *raiz){
    NO *a = *raiz;
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    atualiza_altura(a);
    atualiza_altura(b);
    *raiz = b;
}

static void rotacao_esquerda(ArvAVL *raiz){
    NO *a = *raiz;
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    atualiza_altura(a);
    atualiza_altura(b);
    *raiz = b;
}

/* rebalanceia a raiz apontada */
static void rebalancear(ArvAVL *raiz){
    if(!raiz || !*raiz) return;
    atualiza_altura(*raiz);
    int fb = fator_balanceamento(*raiz);

    if(fb > 1){
        if(fator_balanceamento((*raiz)->esq) < 0)
            rotacao_esquerda(&(*raiz)->esq);   /* LR */
        rotacao_direita(raiz);                  /* LL */
    } else if(fb < -1){
        if(fator_balanceamento((*raiz)->dir) > 0)
            rotacao_direita(&(*raiz)->dir);     /* RL */
        rotacao_esquerda(raiz);                 /* RR */
    }
}

/* API */
static ArvAVL *criarAVL(){
    ArvAVL *r = (ArvAVL*)malloc(sizeof(ArvAVL));
    if(r) *r = NULL;
    return r;
}

static NO* novo_no(int x){
    NO *n = (NO*)malloc(sizeof(NO));
    if(!n) return NULL;
    n->chave = x; n->esq = n->dir = NULL; n->altura = 0;
    return n;
}

static int inserirAVL_rec(ArvAVL *raiz, int x){
    if(!raiz) return 0;
    if(*raiz == NULL){
        *raiz = novo_no(x);
        return *raiz != NULL;
    }
    if(x == (*raiz)->chave) return 0;
    if(x < (*raiz)->chave){
        if(!inserirAVL_rec(&(*raiz)->esq, x)) return 0;
    } else {
        if(!inserirAVL_rec(&(*raiz)->dir, x)) return 0;
    }
    rebalancear(raiz);
    return 1;
}

static int inserirAVL(ArvAVL *raiz, int x){
    return inserirAVL_rec(raiz, x);
}

static int buscarAVL(ArvAVL *raiz, int x){
    if(!raiz) return 0;
    NO *at = *raiz;
    while(at){
        if(x == at->chave) return 1;
        at = (x < at->chave) ? at->esq : at->dir;
    }
    return 0;
}

static NO* maior(NO *n){
    while(n && n->dir) n = n->dir;
    return n;
}

static int removerAVL_rec(ArvAVL *raiz, int x){
    if(!raiz || !*raiz) return 0;
    if(x < (*raiz)->chave){
        if(!removerAVL_rec(&(*raiz)->esq, x)) return 0;
    } else if(x > (*raiz)->chave){
        if(!removerAVL_rec(&(*raiz)->dir, x)) return 0;
    } else {
        if(!(*raiz)->esq || !(*raiz)->dir){
            NO *tmp = (*raiz)->esq ? (*raiz)->esq : (*raiz)->dir;
            free(*raiz);
            *raiz = tmp;
        } else {
            NO *pred = maior((*raiz)->esq);
            (*raiz)->chave = pred->chave;
            removerAVL_rec(&(*raiz)->esq, pred->chave);
        }
    }
    if(*raiz) rebalancear(raiz);
    return 1;
}

static int removerAVL(ArvAVL *raiz, int x){
    return removerAVL_rec(raiz, x);
}

static void preord(NO *n){ if(!n) return; printf("%d ", n->chave); preord(n->esq); preord(n->dir); }
static void emord(NO *n){ if(!n) return; emord(n->esq); printf("%d ", n->chave); emord(n->dir); }
static void posord(NO *n){ if(!n) return; posord(n->esq); posord(n->dir); printf("%d ", n->chave); }

static void imprimirPreOrdem(ArvAVL *r){ if(!r){puts("(nao existe)");return;} preord(*r); puts(""); }
static void imprimirEmOrdem(ArvAVL *r){ if(!r){puts("(nao existe)");return;} emord(*r); puts(""); }
static void imprimirPosOrdem(ArvAVL *r){ if(!r){puts("(nao existe)");return;} posord(*r); puts(""); }

static int tamanhoNO(NO *n){ return n ? 1 + tamanhoNO(n->esq) + tamanhoNO(n->dir) : 0; }
static int tamanhoAVL(ArvAVL *r){ return (!r)?0:tamanhoNO(*r); }
static int alturaAVL(ArvAVL *r){ return (!r || !*r)?-1:(*r)->altura; }

static void liberaNO(NO *n){ if(!n) return; liberaNO(n->esq); liberaNO(n->dir); free(n); }
static void liberarAVL(ArvAVL *r){ if(!r) return; liberaNO(*r); free(r); }

#endif
