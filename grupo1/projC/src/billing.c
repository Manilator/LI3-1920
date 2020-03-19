#include "billing.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

#define N 0
#define P 1

struct fatura
{
    float totalFaturado;
    int unidadesP;
    int unidadesN;
    int filiais[3];
    GHashTable* faturasProduto;
};

struct faturaProduto
{
    float totalFaturadoN;
    int totalFaturadoP;
    int unidadesP;
    int unidadesN;
    int filiaisQnt[3][2];
    float filiaisFaturado[3][2];
};

Fatura initFatura() {
    Fatura new = g_malloc(sizeof(struct fatura));
    new->totalFaturado = 0;
    new->unidadesP = 0;
    new->unidadesN = 0;
    int i;
    for(i = 0; i < 3; i++) {
        new->filiais[i] = 0;
    }
     new->faturasProduto = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeFaturaProduto);
     return new;
}

FaturaProduto initFaturaProduto() {
    FaturaProduto new = g_malloc(sizeof(struct faturaProduto));
    new->totalFaturadoN = 0;
    new->totalFaturadoP = 0;
    new->unidadesP = 0;
    new->unidadesN = 0;
    int i, j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            new->filiaisQnt[i][j] = 0;
            new->filiaisFaturado[i][j] = 0;
        }
    }
    return new;
}

int addFaturaProduto(Fatura f, char* code) {
    FaturaProduto new = initFaturaProduto();
    char* _code = strdup(code);

    strtok(_code, "\r\n");

    if (!g_hash_table_contains(f->faturasProduto,_code)) {
        g_hash_table_insert(f->faturasProduto, (char*)_code, (gpointer)new);
        return 1;
    }
    g_free(_code);
    return 0;
}

void updateFatura(Fatura f, char* code, float tf, int u, char tipo, int filial) {

    f->totalFaturado += tf;
    if(tipo == 'N') {
        f->unidadesN += u;
    } else if (tipo == 'P') {
        f->unidadesP += u;
    }
    f->filiais[filial-1] += u;
    FaturaProduto fp = (FaturaProduto)g_hash_table_lookup(f->faturasProduto, code);
    updateFaturaProduto(fp, tf, u, tipo, filial);
}

int updateFaturaProduto(FaturaProduto fp, float tf, int u, char tipo, int filial) {
    int r = 0;
    if (tipo == 'N') {
        fp->totalFaturadoN += tf;
        fp->unidadesN += u;
        fp->filiaisFaturado[filial-1][N] += tf;
        fp->filiaisQnt[filial-1][N] += u;
        r = 1;
    } else if (tipo == 'P') {
        fp->totalFaturadoP += tf;
        fp->unidadesP += u;
        fp->filiaisFaturado[filial-1][P] += tf;
        fp->filiaisQnt[filial-1][P] += u;
        r = 1;
    }
    return r;
}

float getTotalFaturadoFatura(Fatura f) {
    return f->totalFaturado;
}

FaturaProduto getFaturaProduto(Fatura f, char* product) {
    return g_hash_table_lookup(f->faturasProduto, product);
}

float getTotalFaturadoN_FP(FaturaProduto fp) {
    return fp->totalFaturadoN;
}

char* getFirstKey(Fatura f) {
    guint *size = g_malloc(sizeof(guint));
    *size = 10;
    return (char *)g_hash_table_get_keys_as_array(f->faturasProduto,size)[1];

}

void freeFaturaProduto(FaturaProduto fp) {
    /*printf("Vou dar free das filiaisQnt\n");
    g_free(fp->filiaisQnt);
    printf("Vou dar free das filiaisFaturado\n");
    g_free(fp->filiaisFaturado);*/
    g_free(fp);
}

void freeFatura(Fatura f) {
    /*printf("Vou dar free das filiais\n");
    g_free(f->filiais);*/
    g_hash_table_destroy(f->faturasProduto);
    g_free(f);
}
