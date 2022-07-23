#include "../h/vetor.h"

Vetor* vetor_strings(FILE* arquivo) {
    Vetor* vetor = (Vetor*)malloc(sizeof(Vetor));
    vetor->v = (char**)malloc(TAM_INIC*sizeof(char*));
    vetor->tam = 0;
    int tamMax = TAM_INIC;
    while(1) {
        if(feof(arquivo)) break;

        fscanf(arquivo, " %m[^\n] ", &vetor->v[vetor->tam]);
        vetor->tam++;

        if(vetor->tam >= tamMax){
            tamMax *= 2;
            vetor->v = (char**)realloc(vetor->v, tamMax*sizeof(char*));
        }
    }
    vetor->v = (char**)realloc(vetor->v, vetor->tam*sizeof(char*));

    return vetor;
}

void imprime_vetor(Vetor* vetor) {
    printf("====================================\n");
    printf("O tamanho do vetor eh: %d\n", vetor->tam);
    for(int i = 0; i < vetor->tam; i++)
        printf("%d: %s\n", i, vetor->v[i]);
    printf("====================================\n");
}

void destroi_vetor(Vetor* vetor) {
    for(int i = 0; i < vetor->tam; i++)
        free(vetor->v[i]);
        
    free(vetor->v);
    free(vetor);
}