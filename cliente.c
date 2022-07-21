#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./src/h/vetor.h"
#include "./src/h/grafo.h"
#include "./src/h/indexador.h"

char* append_diretorio(char* diretorio, const char* sufixo);

int main(int argc, char** argv) {
    char* dir = argv[1];

    char* index = append_diretorio(dir, "index.txt");
    char* stopwords = append_diretorio(dir, "stopwords.txt");
    char* graph = append_diretorio(dir, "graph.txt");
    char* pages = append_diretorio(dir, "pages");

    // printf("%s\n", index);
    // printf("%s\n", stopwords);
    // printf("%s\n", graph);

    FILE* fi = fopen(index, "r");
    FILE* fs = fopen(stopwords, "r");
    FILE* fg = fopen(graph, "r");

    if(!fi || !fs || !fg) {
        printf("Erro na abertura dos arquivos!\n");
        exit(1);
    }

    Vetor* vetorIndex = vetor_strings(fi);
    imprime_vetor(vetorIndex);

    Vetor* vetorStopwords = vetor_strings(fs);
    imprime_vetor(vetorStopwords);

    Grafo** g = le_grafo(fg, vetorIndex->tam);
    imprime_grafo(g, vetorIndex->tam);

    RBT* h = RBT_init();
    h = RBT_insere(h, vetorIndex->v[0], vetorIndex->v[1]);
    h = RBT_insere(h, vetorIndex->v[0], vetorIndex->v[4]);
    h = RBT_insere(h, vetorIndex->v[2], vetorIndex->v[3]);
    RBT_imprime(h);


    libera_grafo(g, vetorIndex->tam);
    destroi_vetor(vetorIndex);
    destroi_vetor(vetorStopwords);

    fclose(fi);
    fclose(fs);
    fclose(fg);
        
    free(index);
    free(stopwords);
    free(graph);

    return 0;
}

char* append_diretorio(char* diretorio, const char* sufixo){
    size_t necessario = snprintf(NULL, 0, "%s/%s", diretorio, sufixo);
    char* apnd = (char*) malloc(necessario+1);
    sprintf(apnd, "%s/%s", diretorio, sufixo);

    return apnd;
}

