#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct produto
{
  int codigo;
  char nome[30];
  float preco;
  int quantidade;
};

struct hash
{
  int qtd;
  int TABLE_SIZE;
  struct produto **itens;
};

typedef struct hash Hash;

Hash *criaHash(int tamanho)
{
  Hash *ha = (Hash *)malloc(sizeof(Hash));
  int i;
  if (ha != NULL)
  {
    ha->TABLE_SIZE = tamanho;
    ha->itens = (struct produto **)malloc(tamanho * sizeof(struct produto *));
    if (ha->itens == NULL)
    {
      free(ha);
      return NULL;
    }
    ha->qtd = 0;
    for (i = 0; i < ha->TABLE_SIZE; i++)
      ha->itens[i] = NULL;
  }
  return ha;
}

void liberaHash(Hash *ha)
{
  int i;
  if (ha != NULL)
  {
    for (i = 0; i < ha->TABLE_SIZE; i++)
    {
      if (ha->itens[i] != NULL)
        free(ha->itens[i]);
    }
    free(ha->itens);
    free(ha);
  }
}

int chaveDivisao(int chave, int TABLE_SIZE)
{
  return ((chave & 0x7FFFFFFF) % TABLE_SIZE);
}

int insereHash_EnderAberto(Hash *ha, struct produto p)
{
  int i, pos, newpos;
  int chave = p.codigo;
  if (ha == NULL || ha->qtd == ha->TABLE_SIZE)
  {
    return 0;
  }

  pos = chaveDivisao(chave, ha->TABLE_SIZE);

  for (i = 0; i < ha->TABLE_SIZE; i++)
  {
    newpos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);

    if (ha->itens[newpos] == NULL)
    {
      struct produto *novo = (struct produto *)malloc(sizeof(struct produto));
      if (novo == NULL)
      {
        return 0;
      }
      *novo = p;
      ha->itens[newpos] = novo;
      ha->qtd++;
      return 1;
    }
  }
  return 0;
}

int sondagemQuadratica(int pos, int i, int TABLE_SIZE)
{
  pos = pos + 2 * i + 5 * 1 * 1;
  return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}

int buscaHash_EnderAberto(Hash *ha, int codigo, struct produto *p)
{
  int pos, i, newpos;
  if (ha == NULL)
  {
    return 0;
  }

  pos = chaveDivisao(codigo, ha->TABLE_SIZE);

  for (i = 0; i < ha->TABLE_SIZE; i++)
  {
    newpos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);

    if (ha->itens[newpos] == NULL)
    {
      return 0;
    }
    if (ha->itens[newpos]->codigo == codigo)
    {
      *p = *(ha->itens[newpos]);
      return 1;
    }
  }
  return 0;
}

void imprimeProduto(struct produto p)
{
  printf("Codigo: %d\n", p.codigo);
  printf("Nome: %s\n", p.nome);
  printf("Preco: R$ %.2f\n", p.preco);
  printf("Quantidade: %d\n", p.quantidade);
  printf("\n");
}

void imprimeTabela(Hash *ha)
{
  int i;
  if (ha == NULL)
  {
    printf("Tabela vazia!\n");
    return;
  }

  printf("\nTABELA HASH \n");
  printf("Tamanho: %d\n", ha->TABLE_SIZE);
  printf("Elementos: %d\n", ha->qtd);
  printf("-------------------\n");

  for (i = 0; i < ha->TABLE_SIZE; i++)
  {
    printf("Posicao %d: ", i);
    if (ha->itens[i] == NULL)
      printf("VAZIA\n");
    else
      printf("Codigo %d - %s\n", ha->itens[i]->codigo, ha->itens[i]->nome);
  }
  printf("\n\n");
}

Hash *criaHash(int tamanho);
void liberaHash(Hash *ha);
int chaveDivisao(int chave, int TABLE_SIZE);
int chaveMultiplicacao(int chave, int TABLE_SIZE);

int insereHash_SemColisao(Hash *ha, struct produto p);
int buscaHash_SemColisao(Hash *ha, int codigo, struct produto *p);

int insereHash_EnderAberto(Hash *ha, struct produto p);
int buscaHash_EnderAberto(Hash *ha, int codigo, struct produto *p);

void imprimeProduto(struct produto p);
void imprimeTabela(Hash *ha);

#endif
