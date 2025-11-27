#include <stdio.h>
#include "arvoreBinaria.h"

int main(){
    ArvBin *arv = NULL;
    int criada = 0, op, v;

    do{
        printf("\n MENU ARVORE BINARIA \n");
        printf("0 - Criar arvore\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Buscar\n");
        printf("4 - Pre-ordem\n");
        printf("5 - Em ordem\n");
        printf("6 - Pos-ordem\n");
        printf("7 - Tamanho (numero de nos)\n");
        printf("8 - Liberar arvore\n");
        printf("9 - Sair\n");
        printf("Escolha: ");

        if(scanf("%d",&op)!=1) return 0;

        switch(op){
            case 0:
                if(criada){ puts("Arvore ja criada."); break; }
                arv = cria_ArvBin();
                if(!arv) puts("Erro ao criar.");
                else { criada=1; puts("Arvore criada!"); }
                break;

            case 1:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                printf("Valor: "); scanf("%d",&v);
                puts(insere_ArvBin(arv,v) ? "Inserido!" : "Falha/duplicado.");
                break;

            case 2:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                printf("Valor: "); scanf("%d",&v);
                puts(remove_ArvBin(arv,v) ? "Removido (se existia)!" : "Nao removido.");
                break;

            case 3:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                printf("Valor: "); scanf("%d",&v);
                puts(consulta_ArvBin(arv,v) ? "Encontrado!" : "Nao encontrado.");
                break;

            case 4:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                preOrdem_ArvBin(arv); printf("\n"); break;

            case 5:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                emOrdem_ArvBin(arv); printf("\n"); break;

            case 6:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                posOrdem_ArvBin(arv); printf("\n"); break;

            case 7:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                printf("Tamanho: %d\n", totalNO_ArvBin(arv)); break;

            case 8:
                if(!criada){ puts("Nenhuma arvore criada."); break; }
                libera_ArvBin(arv); arv=NULL; criada=0; puts("Arvore liberada!"); break;

            case 9:
                if(criada) libera_ArvBin(arv);
                puts("Saindo...");
                break;

            default:
                puts("Opcao invalida.");
        }
    } while(op!=9);

    return 0;
}
