#include "glibW.h"
#include <string.h>

#include "product_catalog.h"

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
