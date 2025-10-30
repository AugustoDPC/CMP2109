#include <stdio.h>
#include "arvoreBinaria.h"

int main()
{
  Arvore a;
  int criada = 0;
  int opcao, valor;

  do
  {
    printf("\n==== MENU ARVORE BINARIA ====\n");
    printf("0 - Criar/Iniciar arvore\n");
    printf("1 - Inserir elemento\n");
    printf("2 - Buscar elemento\n");
    printf("3 - Exibir em pre-ordem\n");
    printf("4 - Exibir em ordem\n");
    printf("5 - Exibir em pos-ordem\n");
    printf("6 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 0:
      iniciarArvore(&a);
      criada = 1;
      printf("Arvore criada!\n");
      break;

    case 1:
      if (!criada)
      {
        printf("Crie a arvore primeiro!\n");
        break;
      }
      printf("Digite o valor: ");
      scanf("%d", &valor);
      if (inserir(&a, valor))
        printf("Inserido com sucesso!\n");
      else
        printf("Erro: valor duplicado ou sem espaço.\n");
      break;

    case 2:
      if (!criada)
      {
        printf("Crie a arvore primeiro!\n");
        break;
      }
      printf("Digite o valor: ");
      scanf("%d", &valor);
      if (buscar(&a, valor))
        printf("Valor encontrado!\n");
      else
        printf("Valor nao encontrado!\n");
      break;

    case 3:
      if (!criada)
      {
        printf("Crie a arvore primeiro!\n");
        break;
      }
      printf("Pre-ordem: ");
      preOrdem(&a, 0);
      printf("\n");
      break;

    case 4:
      if (!criada)
      {
        printf("Crie a arvore primeiro!\n");
        break;
      }
      printf("Em ordem: ");
      emOrdem(&a, 0);
      printf("\n");
      break;

    case 5:
      if (!criada)
      {
        printf("Crie a arvore primeiro!\n");
        break;
      }
      printf("Pos-ordem: ");
      posOrdem(&a, 0);
      printf("\n");
      break;

    case 6:
      printf("Saindo...\n");
      break;

    default:
      printf("Opcao invalida!\n");
    }

  } while (opcao != 6);

  return 0;
}
