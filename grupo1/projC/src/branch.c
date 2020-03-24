#include "branch.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct branch
{
    GHashTable* productsClients;
    GHashTable* clientsProducts;
};


struct relationWithClient
{
    GHashTable* infoClients;
    int totalProductsSold; /* Quantity of products that a certain client bought */
};


struct relationWithProduct
{
    GHashTable* infoProducts;
    float totalBilled[12];
};

struct infoClient
{
    int unitsN;
    int unitsP;
};

struct infoProduct
{
    int quantities[12];
    float totalBilled[12];
};

Branch initBranch() {
    Branch new = g_malloc(sizeof(struct branch));
    new->productsClients = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeRelationWithClient);
    new->clientsProducts = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeRelationWithProduct);

    return new;
}

RelationWithClient initRelationWithClient() {
    RelationWithClient new = g_malloc(sizeof(struct relationWithClient));
    new->totalProductsSold = 0;
    new->infoClients = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeInfoClient);

    return new;
}

RelationWithProduct initRelationWithProduct() {
    RelationWithProduct new = g_malloc(sizeof(struct relationWithProduct));
    int i;
    for(i = 0; i < 12; i++) {
        new->totalBilled[i] = 0;
    }
    new->infoProducts = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeInfoProduct);

    return new;
}

InfoClient initInfoClient() {
    InfoClient new = g_malloc(sizeof(struct infoClient));
    new->unitsN = 0;
    new->unitsP = 0;
    return new;
}

InfoProduct initInfoProduct() {
    InfoProduct new = g_malloc(sizeof(struct infoProduct));
    int i;
    for(i = 0; i < 12; i++) {
        new->quantities[i] = 0;
        new->totalBilled[i] = 0;
    }
    return new;
}

void addRelationWithClient(Branch b, char* product_code, RelationWithClient rcc) {
    g_hash_table_insert(b->productsClients, product_code, rcc);
}

void addRelationWithProduct(Branch b, char* client_code, RelationWithProduct rcp) {
    g_hash_table_insert(b->clientsProducts, client_code, rcp);
}
void addInfoClient(RelationWithClient rcc, char* client_code, InfoClient ic) {
    g_hash_table_insert(rcc->infoClients, client_code, ic);
}

void addInfoProduct(RelationWithProduct rcp, char* product_code, InfoProduct ip) {
    g_hash_table_insert(rcp->infoProducts, product_code, ip);
}

void updateBranch(Branch b, char* client_code, char* product_code, int units, char promotion_type, float billed, int month) {
    RelationWithClient rcc = g_hash_table_lookup(b->productsClients, product_code);
    RelationWithProduct rcp = g_hash_table_lookup(b->clientsProducts, client_code);
    if (rcc == NULL) {
        char* _code_product = strdup(product_code);

        strtok(_code_product, "\r\n");
        g_hash_table_insert(b->productsClients, _code_product, initRelationWithClient());
        rcc = g_hash_table_lookup(b->productsClients, _code_product);
    }
    if (rcp == NULL) {
        char* _code_client = strdup(client_code);

        strtok(_code_client, "\r\n");
        g_hash_table_insert(b->clientsProducts, _code_client, initRelationWithProduct());
        rcp = g_hash_table_lookup(b->clientsProducts, _code_client);
    }
    updateRelationWithClient(rcc, client_code, units, promotion_type);
    updateRelationWithProduct(rcp, product_code, units, billed, month);
}

void updateRelationWithProduct(RelationWithProduct rcp, char* product_code, int quantity, float billed, int month) {
    rcp->totalBilled[month-1] += billed;
    InfoProduct ip = g_hash_table_lookup(rcp->infoProducts, product_code);
    if (ip == NULL) {
        char* _code_product = strdup(product_code);

        strtok(_code_product, "\r\n");
        g_hash_table_insert(rcp->infoProducts, _code_product, initInfoProduct());
        ip = g_hash_table_lookup(rcp->infoProducts, _code_product);
    }
    updateInfoProduct(ip,quantity,billed,month);
}

void updateRelationWithClient(RelationWithClient rcc, char* client_code, int units, char promotion_type) {
    rcc->totalProductsSold += units;
    InfoClient ic = g_hash_table_lookup(rcc->infoClients,client_code);
    if (ic == NULL) {
        char* _code_client = strdup(client_code);

        strtok(_code_client, "\r\n");
        g_hash_table_insert(rcc->infoClients, _code_client, initInfoClient());
        ic = g_hash_table_lookup(rcc->infoClients,_code_client);
    }
    updateInfoClient(ic,units,promotion_type);
}

void updateInfoClient(InfoClient ic, int units, char promotion_type) {
    if (promotion_type == 'P') {
        ic->unitsP += units;
    } else if (promotion_type == 'N') {
        ic->unitsN += units;
    }
}

void updateInfoProduct(InfoProduct ip, int quantity, float billed, int month) {
    ip->quantities[month-1] += quantity;
    ip->totalBilled[month-1] += billed;
}

void freeBranch(Branch b) {
    g_hash_table_destroy(b->productsClients);
    g_hash_table_destroy(b->clientsProducts);
    g_free(b);
}

void freeRelationWithClient(RelationWithClient rc) {
    g_hash_table_destroy(rc->infoClients);
    g_free(rc);
}

void freeRelationWithProduct(RelationWithProduct rp) {
    g_hash_table_destroy(rp->infoProducts);
    g_free(rp);
}

void freeInfoClient(InfoClient ic) {
    g_free(ic);
}

void freeInfoProduct(InfoProduct ip) {
    g_free(ip);
}

static int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void sort(const char* arr[], int n) {
    qsort(arr, n, sizeof(const char*), compare);
}

char** getClientCodes(Branch b, int *len) {

    char** codes = (char**)g_hash_table_get_keys_as_array(b->clientsProducts, len);
    printf("[branch.c/getClientCodes] len1 = %d\n", *len);
    sort((const char**)codes, *len);
    printf("[branch.c/getClientCodes] len2 = %d\n", *len);
    return codes;
}
