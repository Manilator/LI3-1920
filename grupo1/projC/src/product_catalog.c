#include "glibW.h"
#include "constants.h"
#include "product_catalog.h"

#include <string.h>
#include <stdlib.h>

struct products
{
    GHashTable* products; /**< Códigos de produto e a sua estrutura */
};

Products initProducts() {
    Products products;
    products = g_malloc(sizeof(struct products));
    products->products = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    return products;
}

static int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

static void sort(const char* arr[], int n) {
    qsort(arr, n, sizeof(const char*), compare);
}


/* QUERIE 2 */
char ** getProductsByLetter(Products products_catalog, char letter){
    GHashTableIter iter;
    gpointer key, value;
    int size = g_hash_table_size(products_catalog->products);
    char** result = g_malloc(sizeof(char*)*(size+1));
    int i=0;

    g_hash_table_iter_init (&iter, products_catalog->products);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        if( ((char*)key)[0] == letter){
            /*result[i] = g_malloc(sizeof(char*));*/
            result[i++] = strdup((char*)key);
        }
    }
    sort((const char**)result, i);
    result[i] = NULL;
    return result;
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
        return ONE;
    }
    g_free(_temp);
    return ZERO;
}

int existProductCode (Products products, char* product_code) {
    if (g_hash_table_contains(products->products, product_code)) {
        return ONE;
    }
    return ZERO;
}

int getSizeProducts(Products products) {
    return g_hash_table_size(products->products);
}

char ** getProductsNotArray(Products product_catalog, GHashTable * products_bought){
    int i=ZERO;
    int size = getSizeProducts(product_catalog) - g_hash_table_size(products_bought);
    char** result = g_malloc(sizeof(char*)*(size+1));

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, product_catalog->products);
    while (g_hash_table_iter_next (&iter, &key, &value))
    {
        if(!g_hash_table_contains(products_bought, (char*)key)){
            result[i++] = (char*)key;
        }
    }
    sort((const char**)result, i);
    result[i]=NULL;
    return result;
}

int getNumberProductsNotUsed(Products product_catalog, GHashTable * products_bought){
    return getSizeProducts(product_catalog) - g_hash_table_size(products_bought);
}

void destroyProducts(Products products) {
    g_hash_table_destroy (products->products);
    g_free(products);
}
