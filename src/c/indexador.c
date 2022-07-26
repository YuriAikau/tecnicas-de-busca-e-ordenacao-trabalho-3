#include "../h/indexador.h"

static int compare(const void* s1, const void* s2){
    char* c1 = *((char**)s1);
    char* c2 = *((char**)s2);

    return strcmp(c1,c2);
}

static char* to_lower(char* str) {
    for(int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);

    return str;
}

char* append_diretorio(char* diretorio, char* sufixo){
    size_t necessario = snprintf(NULL, 0, "%s/%s", diretorio, sufixo);
    char* apnd = (char*) malloc(necessario+1);
    sprintf(apnd, "%s/%s", diretorio, sufixo);

    return apnd;
}

static int busca_binaria_string(char** vet, char* k, int lo, int hi) {
    if(hi < lo)
        return -1;
    
    int mid = lo + (hi-lo)/2;

    int cmp = strcmp(k, vet[mid]);
    if(!cmp)
        return mid;
    else if(cmp < 0)
        return busca_binaria_string(vet, k, lo, mid -1);
    else
        return busca_binaria_string(vet, k, mid + 1, hi);
}

RBT* indexador(Vetor* vetIndex, Vetor* vetStopWords, char* path) {
    qsort(vetStopWords->v, vetStopWords->tam, sizeof(char*), compare);
    // imprime_vetor(vetStopWords);

    RBT* tab_sim = RBT_init();
    
    for(int i = 0; i < vetIndex->tam; i++){
        char* filePath = append_diretorio(path, vetIndex->v[i]);
        FILE* fileTemp = fopen(filePath, "r");

        while(1){
            char* linha = NULL;
            size_t size = 0;

            int n = getline(&linha, &size, fileTemp);
            if(n <= 0) {
                free(linha);
                break;
            }
            
            char* temp = strtok(linha, " \t\n");
            char* splits;
            if(temp) splits = temp;

            while(1) {
                if(!temp) break;
                //printf("%s\n", splits);

                if(busca_binaria_string(vetStopWords->v, to_lower(splits), 0, vetStopWords->tam - 1) < 0)
                    tab_sim = RBT_insere(tab_sim, splits, vetIndex->v[i]);

                temp = strtok(NULL, " \t\n");
                if(temp) splits = temp;
            }
            //free(splits);
            free(linha);
        }
        free(filePath);
        fclose(fileTemp);
    }

    return tab_sim;
}