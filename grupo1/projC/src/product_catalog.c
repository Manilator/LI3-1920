#include "glibW.h"
#include "constants.h"
#include "product_catalog.h"

#include <string.h>


struct products
{
    GHashTable* products;
};

Products initProducts() {
    Products products;
    products = g_malloc(sizeof(struct products));
    products->products = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    return products;
}

/* QUERIE 2 */
GSList * getProductsByLetter(Products products_catalog, char letter){
    GSList *list = NULL;

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, products_catalog->products);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        if( ((char*)key)[0] == letter)
            list = g_slist_append (list, key);
    }


    return list;
}

int addProduct(Products products,char* product) {
    char* product_code = strdup(product);
    strtok(product_code, "\r\n");

    if (verifyProduct(product_code) && !g_hash_table_contains(products->products, product_code)) {
        g_hash_table_insert(products->products, (char*)product_code, (gpointer)newProduct(product_code));
        return 1;
    }
    g_free(product_code);
    return 0;
}

int existProduct (Products products, Product product) {
    char* _temp;
    _temp = getProductCode(product);
    if (g_hash_table_contains(products->products, _temp)) {
        g_free(_temp);
        return 1;
    }
    g_free(_temp);
    return 0;
}

int getSizeProducts(Products products) {
    return g_hash_table_size(products->products);
}

void destroyProducts(Products products) {
    g_hash_table_destroy (products->products);
    g_free(products);
}
