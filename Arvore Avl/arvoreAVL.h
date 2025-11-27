#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO* ArvAVL;


struct NO {
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};


ArvAVL* criarAVL();
void liberarAVL(ArvAVL *raiz);
int inserirAVL(ArvAVL *raiz, int valor);
int removerAVL(ArvAVL *raiz, int valor);
int buscarAVL(ArvAVL *raiz, int valor);
int tamanhoAVL(ArvAVL *raiz);
int alturaAVL(ArvAVL *raiz);
void imprimirPreOrdem(ArvAVL *raiz);
void imprimirEmOrdem(ArvAVL *raiz);
void imprimirPosOrdem(ArvAVL *raiz);



static int altura_NO(struct NO *no) {
    return (no == NULL ? -1 : no->alt);
}

static int maior(int a, int b) {
    return (a > b ? a : b);
}

static int fatorBalanceamento_NO(struct NO *no) {
    return altura_NO(no->esq) - altura_NO(no->dir);
}



static void RotacaoLL(ArvAVL *A) {
    struct NO *B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;

    (*A)->alt = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->alt = maior(altura_NO(B->esq), altura_NO(B->dir)) + 1;

    *A = B;
}

static void RotacaoRR(ArvAVL *A) {
    struct NO *B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;

    (*A)->alt = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->alt = maior(altura_NO(B->esq), altura_NO(B->dir)) + 1;

    *A = B;
}

static void RotacaoLR(ArvAVL *A) {
    RotacaoRR(&((*A)->esq));
    RotacaoLL(A);
}

static void RotacaoRL(ArvAVL *A) {
    RotacaoLL(&((*A)->dir));
    RotacaoRR(A);
}



ArvAVL* criarAVL() {
    ArvAVL *raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}



static void libera_NO(struct NO *no){
    if(no == NULL) return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
}

void liberarAVL(ArvAVL *raiz) {
    if(raiz == NULL) return;
    libera_NO(*raiz);
    free(raiz);
}



int buscarAVL(ArvAVL *raiz, int valor){
    if(raiz == NULL || *raiz == NULL) return 0;

    struct NO *atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info)
            return 1;

        if(valor < atual->info)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    return 0;
}



int inserirAVL(ArvAVL *raiz, int valor) {
    int res;

    if (*raiz == NULL) {
        struct NO *novo = (struct NO*) malloc(sizeof(struct NO));
        novo->info = valor;
        novo->alt = 0;
        novo->esq = novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    if (valor < (*raiz)->info) {
        res = inserirAVL(&((*raiz)->esq), valor);
        if (res && fatorBalanceamento_NO(*raiz) >= 2) {
            if (valor < (*raiz)->esq->info) RotacaoLL(raiz); else RotacaoLR(raiz);
        }
    }
    else if (valor > (*raiz)->info) {
        res = inserirAVL(&((*raiz)->dir), valor);
        if (res && fatorBalanceamento_NO(*raiz) <= -2) {
            if (valor > (*raiz)->dir->info) RotacaoRR(raiz); else RotacaoRL(raiz);
        }
    }
    else {
        return 0; 
    }

    (*raiz)->alt = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    return res;
}



int removerAVL(ArvAVL *raiz, int valor) {
    if (raiz == NULL || *raiz == NULL) return 0;

    int res;

    if (valor < (*raiz)->info) {
        res = removerAVL(&((*raiz)->esq), valor);
        if (res && fatorBalanceamento_NO(*raiz) <= -2) {
            if (fatorBalanceamento_NO((*raiz)->dir) <= 0) RotacaoRR(raiz);
            else RotacaoRL(raiz);
        }
    }
    else if (valor > (*raiz)->info) {
        res = removerAVL(&((*raiz)->dir), valor);
        if (res && fatorBalanceamento_NO(*raiz) >= 2) {
            if (fatorBalanceamento_NO((*raiz)->esq) >= 0) RotacaoLL(raiz);
            else RotacaoLR(raiz);
        }
    }
    else {
        struct NO *q = *raiz;
        if (q->esq == NULL || q->dir == NULL) {
            struct NO *temp = q->esq ? q->esq : q->dir;
            free(q);
            *raiz = temp;
        }
        else {
            struct NO *temp = q->dir;
            while (temp->esq != NULL)
                temp = temp->esq;
            q->info = temp->info;
            removerAVL(&(q->dir), temp->info);
        }

        if (*raiz != NULL)
            (*raiz)->alt = maior(altura_NO((*raiz)->esq),
                                 altura_NO((*raiz)->dir)) + 1;

        return 1;
    }

    if (*raiz != NULL)
        (*raiz)->alt = maior(altura_NO((*raiz)->esq),
                             altura_NO((*raiz)->dir)) + 1;

    return res;
}


static int totalNO(ArvAVL *raiz){
    if (raiz == NULL || *raiz == NULL) return 0;
    return 1 + totalNO(&((*raiz)->esq)) + totalNO(&((*raiz)->dir));
}

int tamanhoAVL(ArvAVL *raiz){
    return totalNO(raiz);
}



int alturaAVL(ArvAVL *raiz){
    if (raiz == NULL || *raiz == NULL) return -1;
    return (*raiz)->alt;
}


void imprimirPreOrdem(ArvAVL *raiz){
    if (raiz == NULL || *raiz == NULL) return;
    printf("%d ", (*raiz)->info);
    imprimirPreOrdem(&((*raiz)->esq));
    imprimirPreOrdem(&((*raiz)->dir));
}

void imprimirEmOrdem(ArvAVL *raiz){
    if (raiz == NULL || *raiz == NULL) return;
    imprimirEmOrdem(&((*raiz)->esq));
    printf("%d ", (*raiz)->info);
    imprimirEmOrdem(&((*raiz)->dir));
}

void imprimirPosOrdem(ArvAVL *raiz){
    if (raiz == NULL || *raiz == NULL) return;
    imprimirPosOrdem(&((*raiz)->esq));
    imprimirPosOrdem(&((*raiz)->dir));
    printf("%d ", (*raiz)->info);
}

#endif
