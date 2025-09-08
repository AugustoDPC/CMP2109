#include <stdlib.h>
#include <string.h>
#include "TabelaHash.h"

struct produto{
    int codigo;
    char nome[30];
    float preco;
    int qntd;
}

struct hash{
    int qntd, TABLE_SIZE;
    struct produto **itens;
}
typedef struct hash Hash;

Hash* criaHash(int tamanho);
void liberaHash(Hash* ha);
int valorString(char *str);
int insereHash_semColisao(Hash* ha, struct aluno al);
int buscaHash_SemColisao(Hash* ha, struct aluno al, int mat);
int insereHash_EnderAberto(Hash* ha, struct aluno al);
int buscaHash_EnderAberto(Hash* ha, struct aluno al, int mat);