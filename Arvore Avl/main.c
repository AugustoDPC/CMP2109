#include <stdio.h>
#include "arvoreAVL.h"

int main(){
    ArvAVL *avl = NULL;
    int criada = 0, op, v;

    do{
        printf("\n==== MENU AVL ====\n");
        printf("0 - Criar arvore\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Buscar\n");
        printf("4 - Pre-ordem\n");
        printf("5 - Em ordem\n");
        printf("6 - Pos-ordem\n");
        printf("7 - Tamanho\n");
        printf("8 - Altura\n");
        printf("9 - Liberar arvore\n");
        printf("10 - Sair\n");
        printf("Escolha: ");
        if(scanf("%d",&op)!=1) return 0;

        switch(op){
            case 0:
                if(criada){ puts("Arvore ja criada."); break; }
                avl = criarAVL();
                if(!avl) puts("Erro ao criar.");
                else { criada=1; puts("Arvore criada!"); }
                break;
            case 1:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                printf("Valor: "); scanf("%d",&v);
                puts(inserirAVL(avl,v) ? "Inserido!" : "Falha/duplicado.");
                break;
            case 2:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                printf("Valor: "); scanf("%d",&v);
                puts(removerAVL(avl,v) ? "Removido (se existia)!" : "Nao removido.");
                break;
            case 3:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                printf("Valor: "); scanf("%d",&v);
                puts(buscarAVL(avl,v) ? "Encontrado!" : "Nao encontrado.");
                break;
            case 4:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                imprimirPreOrdem(avl); break;
            case 5:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                imprimirEmOrdem(avl); break;
            case 6:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                imprimirPosOrdem(avl); break;
            case 7:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                printf("Tamanho: %d\n", tamanhoAVL(avl)); break;
            case 8:
                if(!criada){ puts("Crie a arvore primeiro!"); break; }
                printf("Altura: %d\n", alturaAVL(avl)); break;
            case 9:
                if(!criada){ puts("Nenhuma arvore criada."); break; }
                liberarAVL(avl); avl=NULL; criada=0; puts("Arvore liberada!"); break;
            case 10:
                if(criada) liberarAVL(avl);
                puts("Saindo..."); break;
            default: puts("Opcao invalida.");
        }
    }while(op!=10);

    return 0;
}
