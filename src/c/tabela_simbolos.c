#include "../h/tabela_simbolos.h"

static char* to_lower(char* str) {
    for(int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);

    return str;
}

static int compare(char* s1, char* s2){
    char* c1 = to_lower(s1);
    char* c2 = to_lower(s2);

    return strcmp(c1,c2);
}

RBT* RBT_init() {
    return NULL;
}

Value busca(RBT *n, Key key) {
    while (n != NULL) {
        int cmp;
        cmp = compare(key, n->chave);
        if (cmp < 0) n = n->e;
        else if (cmp > 0) n = n->d;
        else return n->val;
    }
    return NULL_Value;
}

bool eh_vermelha(RBT *x) {
    if (x == NULL) return PRETO;
    return x->cor; //VERMELHO == true
}

RBT* rotaciona_esquerda(RBT *h) {
    RBT *x = h->d;
    h->d = x->e;
    x->e = h;
    x->cor = x->e->cor;
    x->e->cor = VERMELHO;
    return x;
}

RBT* rotaciona_direita(RBT *h) {
    RBT *x = h->e;
    h->e = x->d;
    x->d = h;
    x->cor = x->d->cor;
    x->d->cor = VERMELHO;
    return x;
}

void troca_cores(RBT *h) {
    h->cor = VERMELHO;
    h->e->cor = PRETO;
    h->d->cor = PRETO;
}

RBT* cria_no(Key chave, char* val, bool cor){
    RBT* no = (RBT*)malloc(sizeof(RBT));

    no->chave = strdup(chave);
    no->val = inicia_lista(); insere_na_lista(no->val, val);
    no->cor = cor;
    no->e = NULL; no->d = NULL;

    return no;
}

RBT* RBT_insere(RBT *h, Key key, char* val) {
    // Insert at bottom and color it VERMELHO.
    if (h == NULL) { return cria_no(key, val, VERMELHO); }

    int cmp = compare(key, h->chave);
    if (cmp < 0) { h->e = RBT_insere(h->e, key, val); }
    else if (cmp > 0) { h->d = RBT_insere(h->d, key, val); }
    else /*cmp == 0*/ { insere_na_lista(h->val, val); }

    //Lean left.
    if(eh_vermelha(h->d) && !eh_vermelha(h->e)) { h = rotaciona_esquerda(h); }
    //Balance 4-node.
    if(eh_vermelha(h->e) && eh_vermelha(h->e->e)) { h = rotaciona_direita(h); }
    //Split 4-node.
    if(eh_vermelha(h->e) && eh_vermelha(h->d)) { troca_cores(h); }
    
    return h;
}

static void rec_imprime(RBT* h, int level) {
    if(h) {
        rec_imprime(h->d, level + 1);
        for(int i = 0; i < level; i++)
            printf("                    ");
        printf("<%s>, ", h->chave);
        imprime_lista(h->val);
        putchar('\n');
        rec_imprime(h->e, level + 1);
    }
}

void RBT_imprime(RBT* h) {
    rec_imprime(h, 0);
}

static void libera_no(RBT* no) {
    free(no->chave);
    destroi_lista(no->val);
    free(no);
}

void RBT_libera(RBT* h) {
    if(!h)
        return;
    
    if(!h->e && !h->d) {
        free(h->chave);
        destroi_lista(h->val);
        free(h);
        return;
    }

    RBT_libera(h->e);
    RBT_libera(h->d);

    free(h->chave);
    destroi_lista(h->val);
    free(h);
}