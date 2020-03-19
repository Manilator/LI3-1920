#include "billing_catalog.h"

#include <glib.h>
#include <stdio.h>


struct faturas
{
    GHashTable* faturas;
};

Faturas initFaturas() {
    Faturas new = g_malloc(sizeof(struct faturas));
    new->faturas = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (gpointer)freeFatura);
    int month;

    for (month = 1; month < 13; month++) {
        addFatura(new, initFatura(), month);
    }

    return new;
}

void addFatura(Faturas faturas, Fatura fatura, int month) {
    int *mes = g_malloc(sizeof(int));
    *mes = month;
    g_hash_table_insert(faturas->faturas, mes, fatura);
}

void updateFaturas(Faturas fs, Sale sale) {
    int *mes = g_malloc(sizeof(int));
    *mes = getMonth(sale);
    Fatura exist = (Fatura)g_hash_table_lookup(fs->faturas,mes);
    updateFatura(exist, getProduct(sale), getPrice(sale) * getUnits(sale), getUnits(sale), getPromotion(sale), getBranch(sale));
    g_free(mes);
    /*g_hash_table_replace(fs->faturas,mes,exist);*/
}

Fatura getFatura(Faturas f, int month) {
    int* key = g_malloc(sizeof(int));
    *key = month;
    Fatura r = (Fatura)g_hash_table_lookup(f->faturas, key);
    g_free(key);
    return r;
}

void freeFaturas(Faturas f) {
    g_hash_table_destroy(f->faturas);
    g_free(f);
}
