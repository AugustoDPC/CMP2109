#include "tabela_hash.h"

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
