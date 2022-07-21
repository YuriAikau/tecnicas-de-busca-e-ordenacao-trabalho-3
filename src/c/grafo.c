#include "../h/grafo.h"

Grafo* init_grafo(char* chave) {
    Grafo* graf = (Grafo*)malloc(sizeof(Grafo));
    graf->chave = chave;
    graf->adjacencias = inicia_lista();

    return graf;
}

Grafo** le_grafo(FILE* fg, int tam) {
    Grafo** g = (Grafo**) malloc(tam*sizeof(Grafo*));
    
    for(int i = 0; i < tam; i++) {
        char* linha = NULL;
        size_t size = 0;
        getline(&linha, &size, fg);

        g[i] = init_grafo(strtok(linha, " "));

        int n = atoi(strtok(NULL, " "));
        for(int j = 0; j < n; j++)
            insere_na_lista(g[i]->adjacencias, strtok(NULL, " \n"));
    }

    return g;
}

void imprime_grafo(Grafo** g, int tam) {
    for(int i = 0; i < tam; i++) {
        printf("%s | ", g[i]->chave);
        imprime_lista(g[i]->adjacencias);
        printf("\n");
    }
}

void libera_grafo(Grafo** g, int tam) {
    for(int i = 0; i < tam; i++) {
        free(g[i]->chave);
        destroi_lista(g[i]->adjacencias);
        free(g[i]);
    }
    free(g);
}