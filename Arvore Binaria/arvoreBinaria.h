#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#include <stdio.h>

#define MAX 100

typedef struct
{
  int arvoreBinaria[MAX];
} Arvore;

int esquerda(int i) { return 2 * i + 1; }
int direita(int i) { return 2 * i + 2; }

void iniciarArvore(Arvore *a)
{
  for (int i = 0; i < MAX; i++)
  {
    a->arvoreBinaria[i] = -1;
  }
}

int inserir(Arvore *a, int valor)
{
  int i = 0;
  while (i < MAX)
  {
    if (a->arvoreBinaria[i] == -1)
    {
      a->arvoreBinaria[i] = valor;
      return 1;
    }
    if (valor == a->arvoreBinaria[i])
    {
      return 0;
    }
    if (valor < a->arvoreBinaria[i])
      i = esquerda(i);
    else
      i = direita(i);
  }
  return 0;
}

int buscar(Arvore *a, int valor)
{
  int i = 0;
  while (i < MAX && a->arvoreBinaria[i] != -1)
  {
    if (valor == a->arvoreBinaria[i])
      return 1;
    if (valor < a->arvoreBinaria[i])
      i = esquerda(i);
    else
      i = direita(i);
  }
  return 0;
}

void preOrdem(Arvore *a, int i)
{
  if (i >= MAX || a->arvoreBinaria[i] == -1)
    return;
  printf("%d ", a->arvoreBinaria[i]);
  preOrdem(a, esquerda(i));
  preOrdem(a, direita(i));
}

void emOrdem(Arvore *a, int i)
{
  if (i >= MAX || a->arvoreBinaria[i] == -1)
    return;
  emOrdem(a, esquerda(i));
  printf("%d ", a->arvoreBinaria[i]);
  emOrdem(a, direita(i));
}

void posOrdem(Arvore *a, int i)
{
  if (i >= MAX || a->arvoreBinaria[i] == -1)
    return;
  posOrdem(a, esquerda(i));
  posOrdem(a, direita(i));
  printf("%d ", a->arvoreBinaria[i]);
}

#endif
