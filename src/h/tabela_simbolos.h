#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"

#define VERMELHO    true
#define PRETO       false

#define NULL_Value  NULL
#define NULL_Key    NULL

#define Key char*
#define Value Lista*

typedef struct node RBT;

struct node {
    Key chave;
    Value val;
    bool cor;
    RBT *e, *d;
};

RBT* RBT_init();
Value busca(RBT *n, Key key);
RBT* RBT_insere(RBT *h, Key key, char* val);
void RBT_imprime(RBT* h);

#endif