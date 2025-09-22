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
