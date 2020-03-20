#include "billing_catalog.h"

#include <glib.h>
#include <stdio.h>


struct billings
{
    GHashTable* billings;
};

Billings initBillings() {
    Billings new = g_malloc(sizeof(struct billings));
    new->billings = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (gpointer)freeBilling);
    int month;

    for (month = 1; month < 13; month++) {
        addBilling(new, initBilling(), month);
    }

    return new;
}

void addBilling(Billings billings, Billing billing, int month) {
    int *mes = g_malloc(sizeof(int));
    *mes = month;
    g_hash_table_insert(billings->billings, mes, billing);
}

void updateBillings(Billings bs, Sale sale) {
    int *mes = g_malloc(sizeof(int));
    *mes = getMonth(sale);
    Billing exist = (Billing)g_hash_table_lookup(bs->billings,mes);
    updateBilling(exist, getProduct(sale), getPrice(sale) * getUnits(sale), getUnits(sale), getPromotion(sale), getBranch(sale));
    g_free(mes);
    /*g_hash_table_replace(fs->billings,mes,exist);*/
}

Billing getBilling(Billings bs, int month) {
    int* key = g_malloc(sizeof(int));
    *key = month;
    Billing r = (Billing)g_hash_table_lookup(bs->billings, key);
    g_free(key);
    return r;
}

void destroyBillings(Billings bs) {
    g_hash_table_destroy(bs->billings);
    g_free(bs);
}
