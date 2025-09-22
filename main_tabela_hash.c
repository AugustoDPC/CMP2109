#include "tabela_hash.h"

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
  int pos, i, j;
  if (ha == NULL || ha->qtd == ha->TABLE_SIZE)
    return 0;

  pos = chaveDivisao(p.codigo, ha->TABLE_SIZE);

  for (i = 0; i < ha->TABLE_SIZE; i++)
  {
    j = (pos + i) % ha->TABLE_SIZE;

    if (ha->itens[j] == NULL)
    {
      ha->itens[j] = (struct produto *)malloc(sizeof(struct produto));
      if (ha->itens[j] == NULL)
        return 0;
      *(ha->itens[j]) = p;
      ha->qtd++;
      return 1;
    }
    if (ha->itens[j]->codigo == p.codigo)
    {
      *(ha->itens[j]) = p;
      return 1;
    }
  }
  return 0;
}

int buscaHash_EnderAberto(Hash *ha, int codigo, struct produto *p)
{
  int pos, i, j;
  if (ha == NULL)
    return 0;

  pos = chaveDivisao(codigo, ha->TABLE_SIZE);

  for (i = 0; i < ha->TABLE_SIZE; i++)
  {
    j = (pos + i) % ha->TABLE_SIZE;

    if (ha->itens[j] == NULL)
    {
      return 0;
    }
    if (ha->itens[j]->codigo == codigo)
    {
      *p = *(ha->itens[j]);
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
  printf("-------------------\n");
}

void imprimeTabela(Hash *ha)
{
  int i;
  if (ha == NULL)
  {
    printf("Tabela vazia!\n");
    return;
  }

  printf("\n=== TABELA HASH ===\n");
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
  printf("===================\n\n");
}

int main()
{
  int opcao;
  Hash *tabela = criaHash(10);

  if (tabela == NULL)
  {
    printf("Erro ao criar tabela hash!\n");
    return 1;
  }

  do
  {
    printf("\n=== MENU ===\n");
    printf("1 - Inserir produto\n");
    printf("2 - Buscar produto\n");
    printf("3 - Mostrar tabela\n");
    printf("4 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
    {
      struct produto p;
      printf("Codigo: ");
      scanf("%d", &p.codigo);
      printf("Nome: ");
      scanf(" %[^\n]", p.nome);
      printf("Preco: ");
      scanf("%f", &p.preco);
      printf("Quantidade: ");
      scanf("%d", &p.quantidade);

      if (insereHash_EnderAberto(tabela, p))
        printf("Produto inserido com sucesso!\n");
      else
        printf("Erro: tabela cheia ou falha na alocacao.\n");
      break;
    }
    case 2:
    {
      int codigo;
      struct produto encontrado;
      printf("Codigo para busca: ");
      scanf("%d", &codigo);

      if (buscaHash_EnderAberto(tabela, codigo, &encontrado))
      {
        printf("Produto encontrado:\n");
        imprimeProduto(encontrado);
      }
      else
      {
        printf("Produto nao encontrado!\n");
      }
      break;
    }
    case 3:
      imprimeTabela(tabela);
      break;
    case 4:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida!\n");
    }

  } while (opcao != 4);

  liberaHash(tabela);
  return 0;
}
