#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;

Lista* inicia_lista();
void insere_na_lista(Lista* lista, char* string);
void retira_na_lista(Lista* lista, int posicao);
void imprime_lista(Lista* lista);
void destroi_lista(Lista* lista);

#endif