#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./src/h/vetor.h"

char* append(char* diretorio, const char* sufixo);

int main(int argc, char** argv) {
    char* dir = argv[1];

    char* index = append(dir, "index.txt");
    char* stopwords = append(dir, "stopwords.txt");
    char* graph = append(dir, "graph.txt");

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

char* append(char* diretorio, const char* sufixo){
    size_t necessario = snprintf(NULL, 0, "%s/%s", diretorio, sufixo);
    char* apnd = (char*) malloc(necessario+1);
    sprintf(apnd, "%s/%s", diretorio, sufixo);

    return apnd;
}

