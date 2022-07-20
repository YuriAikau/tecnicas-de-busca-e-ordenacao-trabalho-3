#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

typedef struct grafo_t {
    char* chave;
    Lista* adjacencias;
} Grafo;

Grafo** le_grafo(FILE* fg, int tam);
void imprime_grafo(Grafo** g, int tam);
void libera_grafo(Grafo** g, int tam);

#endif