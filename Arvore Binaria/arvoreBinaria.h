#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info;
    struct NO *esq;
    struct NO *dir;
} NO;


typedef NO* ArvBin;


ArvBin *criarArvore() {
    ArvBin *raiz = (ArvBin *) malloc(sizeof(ArvBin));
    if (raiz != NULL) {
        *raiz = NULL; // árvore começa vazia
    }
    return raiz;
}


int inserir(ArvBin *raiz, int valor) {
    if (raiz == NULL) return 0;

    NO *novo = (NO *) malloc(sizeof(NO));
    if (novo == NULL) return 0;

    novo->info = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    if (*raiz == NULL) {
        
        *raiz = novo;
        return 1;
    }

  
    NO *atual = *raiz;
    NO *pai = NULL;

    while (atual != NULL) {
        pai = atual;

        if (valor == atual->info) {
            free(novo);
            return 0;
        } else if (valor < atual->info) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (valor < pai->info)
        pai->esq = novo;
    else
        pai->dir = novo;

    return 1;
}

int buscar(ArvBin *raiz, int valor) {
    if (raiz == NULL) return 0;
    NO *atual = *raiz;

    while (atual != NULL) {
        if (valor == atual->info)
            return 1;
        else if (valor < atual->info)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    return 0;
}

void preOrdem_NO(NO *no) {
    if (no == NULL) return;
    printf("%d ", no->info);
    preOrdem_NO(no->esq);
    preOrdem_NO(no->dir);
}

void emOrdem_NO(NO *no) {
    if (no == NULL) return;
    emOrdem_NO(no->esq);
    printf("%d ", no->info);
    emOrdem_NO(no->dir);
}

void posOrdem_NO(NO *no) {
    if (no == NULL) return;
    posOrdem_NO(no->esq);
    posOrdem_NO(no->dir);
    printf("%d ", no->info);
}

void libera_NO(NO *no) {
    if (no == NULL) return;

    libera_NO(no->esq); 
    libera_NO(no->dir); 
    free(no);           
}

//* libera_ArvBin:
void libera_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) return;
    libera_NO(*raiz);  
    free(raiz);        
}

void imprimirPreOrdem(ArvBin *raiz) {
    if (raiz == NULL) { printf("(arvore nao existe)\n"); return; }
    preOrdem_NO(*raiz);
    printf("\n");
}

void imprimirEmOrdem(ArvBin *raiz) {
    if (raiz == NULL) { printf("(arvore nao existe)\n"); return; }
    emOrdem_NO(*raiz);
    printf("\n");
}

void imprimirPosOrdem(ArvBin *raiz) {
    if (raiz == NULL) { printf("(arvore nao existe)\n"); return; }
    posOrdem_NO(*raiz);
    printf("\n");
}

#endif