#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;


Lista* iniciaLista();

void insereNaLista(Lista* lista, Matriz* matriz);

void retiraNaLista(Lista* lista, int posicao);

void imprimeLista(Lista* lista);

void destroiLista(Lista* lista);

#endif