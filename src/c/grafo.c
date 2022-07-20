#include "../h/grafo.h"

Grafo** le_grafo(FILE* fg, int tam) {
    char* linha = NULL;
    size_t size = 0;

    Grafo** g = (Grafo**) malloc(tam*sizeof(Grafo*));
    
    for(int i = 0; i < tam; i++) {
        getline(&linha, &size, fg);
        g[i]->chave = strtok(linha, " ");

        g[i]->adjacencias = inicia_lista();
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
    for(int i = 0; i < tam; i++){
        destroi_lista(g[i]->adjacencias);
    }
    free(g);
}