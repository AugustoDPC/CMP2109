
#include <stdio.h>
#include "arvoreBinaria.h"

int main() {
    ArvBin *arvore = NULL;
    int criada = 0;
    int opcao;
    int valor;

    do {
        printf("\n==== MENU ARVORE BINARIA ====\n");
        printf("0 - Criar arvore\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Buscar elemento\n");
        printf("3 - Mostrar pre-ordem\n");
        printf("4 - Mostrar em ordem\n");
        printf("5 - Mostrar pos-ordem\n");
        printf("6 - Liberar arvore da memoria\n");
        printf("7 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
        case 0:
            if (criada) {
                printf("Arvore ja criada.\n");
                break;
            }
            arvore = criarArvore();
            if (arvore == NULL) {
                printf("Erro ao criar arvore.\n");
            } else {
                criada = 1;
                printf("Arvore criada!\n");
            }
            break;

        case 1:
            if (!criada) { printf("Crie a arvore primeiro!\n"); break; }
            printf("Valor para inserir: ");
            scanf("%d", &valor);
            if (inserir(arvore, valor))
                printf("Inserido!\n");
            else
                printf("Nao inserido (duplicado ou erro).\n");
            break;

        case 2:
            if (!criada) { printf("Crie a arvore primeiro!\n"); break; }
            printf("Valor para buscar: ");
            scanf("%d", &valor);
            if (buscar(arvore, valor))
                printf("Valor encontrado!\n");
            else
                printf("Valor nao encontrado.\n");
            break;

        case 3:
            if (!criada) { printf("Crie a arvore primeiro!\n"); break; }
            printf("Pre-ordem: ");
            imprimirPreOrdem(arvore);
            break;

        case 4:
            if (!criada) { printf("Crie a arvore primeiro!\n"); break; }
            printf("Em ordem: ");
            imprimirEmOrdem(arvore);
            break;

        case 5:
            if (!criada) { printf("Crie a arvore primeiro!\n"); break; }
            printf("Pos-ordem: ");
            imprimirPosOrdem(arvore);
            break;

        case 6:
            if (!criada) {
                printf("Nenhuma arvore criada ainda.\n");
                break;
            }
            libera_ArvBin(arvore);
            arvore = NULL;
            criada = 0;
            printf("Arvore liberada da memoria!\n");
            break;

        case 7:
            printf("Saindo...\n");
            if (criada) {
                libera_ArvBin(arvore);
            }
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 7);

    return 0;
}
