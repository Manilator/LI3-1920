#include "branch_catalog.h"


#include <glib.h>

struct filiais 
{
    GHashTable* filiais;
};

Filiais initFiliais(int filiais) {
    Filiais new = g_malloc(sizeof(struct filiais));
    new->filiais = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (gpointer)freeFilial);
    int n_filial;

    for (n_filial = 1; n_filial <= filiais; n_filial++) {
        addFilial(new, initFilial(), n_filial);
    }
    return new;
}

void addFilial(Filiais filiais, Filial filial, int number) {
    int *nr = g_malloc(sizeof(int));
    *nr = number;
    g_hash_table_insert(filiais->filiais, nr, filial);
}

void updateFiliais(Filiais filiais, Sale sale) {
    int *n_filial = g_malloc(sizeof(int));
    *n_filial = getBranch(sale);
    Filial exist = (Filial)g_hash_table_lookup(filiais->filiais,n_filial);
    updateFilial(exist, getClient(sale), getProduct(sale), getUnits(sale), getPromotion(sale), getUnits(sale) * getPrice(sale), getMonth(sale));
    g_free(n_filial);
}

void freeFiliais(Filiais fs) {
    g_hash_table_destroy(fs->filiais);
    g_free(fs);
}
