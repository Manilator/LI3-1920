#include "branch.h"
#include "constants.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct branch
{
    GHashTable* productsClients; /**< Códigos de produtos e a sua estrutura atribuída RelationWithClient */
    GHashTable* clientsProducts; /**< Códigos de clientes e a sua estrutura atribuída RelationWithProduct */
};


struct relationWithClient
{
    GHashTable* infoClients; /**< Códigos de clientes e a sua estrutura atribuída InfoClient */
    int totalProductsSold; /**< Quantidade de produtos que um certo cliente comprou */
};


struct relationWithProduct
{
    GHashTable* infoProducts; /**< Códigos de produto e a sua estrutura atribuída InfoProduct */
    double totalBilled[12]; /**< Faturação total por cada mês */
};

struct infoClient
{
    int unitsN; /**< Número de unidades do tipo N */
    int unitsP; /**< Número de unidades do tipo P */
};

struct infoProduct
{
    int quantities[12]; /**< Quantidades por cada mês */
    double totalBilled[12]; /**< Faturação total por cada mês */
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

void addRelationWithClient(Branch branch, char* product_code, RelationWithClient rcc) {
    g_hash_table_insert(branch->productsClients, product_code, rcc);
}

void addRelationWithProduct(Branch branch, char* client_code, RelationWithProduct rcp) {
    g_hash_table_insert(branch->clientsProducts, client_code, rcp);
}
void addInfoClient(RelationWithClient rcc, char* client_code, InfoClient ic) {
    g_hash_table_insert(rcc->infoClients, client_code, ic);
}

void addInfoProduct(RelationWithProduct rcp, char* product_code, InfoProduct ip) {
    g_hash_table_insert(rcp->infoProducts, product_code, ip);
}

void updateBranch(Branch b, char* client_code, char* product_code, int units, char promotion_type, double billed, int month) {
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

void updateRelationWithProduct(RelationWithProduct rcp, char* product_code, int quantity, double billed, int month) {
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

void updateInfoProduct(InfoProduct ip, int quantity, double billed, int month) {
    ip->quantities[month-1] += quantity;
    ip->totalBilled[month-1] += billed;
}

void freeBranch(Branch branch) {
    g_hash_table_destroy(branch->productsClients);
    g_hash_table_destroy(branch->clientsProducts);
    g_free(branch);
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

static void sort(const char* arr[], int n) {
    qsort(arr, n, sizeof(const char*), compare);
}

char** getClientCodes(Branch branch, int *n) {
    guint * len = g_malloc(sizeof(guint));
    char** codes = (char**)g_hash_table_get_keys_as_array(branch->clientsProducts, len);
    sort((const char**)codes, *len);
    *n = *len;
    g_free(len);
    return codes;
}

char ** getProductsInBranch(Branch b) {
    guint * len = g_malloc(sizeof(guint));
    *len = g_hash_table_size(b->productsClients);
    char ** result = (char**)g_hash_table_get_keys_as_array(b->productsClients, len);
    g_free(len);
    return result;
}

Query9Aux productBoughtBy(Branch b, char *product_code)
{
    RelationWithClient rcc = g_hash_table_lookup(b->productsClients, product_code);
    InfoClient ic;
    int size = g_hash_table_size(rcc->infoClients);

    Query9Aux aux = initQuery9Aux(size);

    GHashTableIter iter;
    gpointer key, value;
    int i = 0, j = 0;

    g_hash_table_iter_init (&iter, rcc->infoClients);
    while (g_hash_table_iter_next (&iter, &key, &value)) {

        ic = (InfoClient)value;

        if (ic->unitsN)
        {
            updateTotalN(aux);
            updateClientsN(aux, i, key);
            i++;
        }

        if (ic->unitsP)
        {
            updateTotalP(aux);
            updateClientsP(aux, j, key);
            j++;
        }
    }
    updateClients(aux, i, j);
    return aux;
}

int * getClientShopLog(Branch b, char* client_code){
    RelationWithProduct rp = g_hash_table_lookup(b->clientsProducts,client_code);
    int * quantities = g_malloc(sizeof(int)*12);
    int i;

    for(i=ZERO;i<12;i++)
        quantities[i] = 0;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, rp->infoProducts);
    while (g_hash_table_iter_next (&iter, &key, &value))
        for(i=ZERO;i<12;i++)
            quantities[i] += ((InfoProduct)value)->quantities[i];

    return quantities;
}

char ** getClientsInBranch(Branch branch){
    guint * len = g_malloc(sizeof(guint));
    *len = g_hash_table_size(branch->clientsProducts);
    char ** result = (char**)g_hash_table_get_keys_as_array(branch->clientsProducts, len);
    g_free(len);
    return result;
}


void getMostBoughtByBranch(Branch b, char* client_code, int month, GHashTable * _mostBought){
    RelationWithProduct rp = g_hash_table_lookup(b->clientsProducts,client_code);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, rp->infoProducts);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        if(g_hash_table_contains(_mostBought, (char*)key)){
            Info info = (Info)(g_hash_table_lookup(_mostBought, (char*)key));
            updateInfo(info, (int)((InfoProduct)value)->quantities[month]);
        }
        else if((int)((InfoProduct)value)->quantities[month] != 0){
            Info info = (Info)initInfo((char*)key, (int)((InfoProduct)value)->quantities[month]);
            g_hash_table_insert(_mostBought, strdup((char*)key), (gpointer)info);
        }
    }
}

void intersectClients(Branch b, GHashTable * _mostBought){
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, b->clientsProducts);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        if(!g_hash_table_contains(_mostBought, (char*)key)){
            g_hash_table_steal(_mostBought, (char*)key);
        }
    }
}

void updateNMostBought(Branch b, GHashTable * _mostBought, int branch){

    GHashTableIter iter2;
    gpointer key2, value2;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, b->clientsProducts);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        RelationWithProduct rp = (RelationWithProduct)value;
        g_hash_table_iter_init (&iter2, rp->infoProducts);
        while (g_hash_table_iter_next (&iter2, &key2, &value2)){
            if(g_hash_table_contains(_mostBought, (char*)key2)){
                Aux aux = (Aux)g_hash_table_lookup(_mostBought, (char*)key2);
                updateAux(aux, branch, (int*)((InfoProduct)value2)->quantities);
            }
            else{
                Aux aux = (Aux)initAux((char*)key2, branch, (int*)((InfoProduct)value2)->quantities);
                g_hash_table_insert(_mostBought, strdup((char*)key2), (gpointer)aux);
            }
        }
    }
}

void clientSpentMostOnBranch(Branch b, char* client_code, GHashTable * _maxSpent)
{
    RelationWithProduct rp = g_hash_table_lookup(b->clientsProducts,client_code);

    int month;
    double spent;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, rp->infoProducts);
    while (g_hash_table_iter_next (&iter, &key, &value))
    {
        spent = 0;
        for(month = 0; month < 12; month++)
        {
            spent += (double)((InfoProduct)value)->totalBilled[month];
        }
        if(g_hash_table_contains(_maxSpent, (char*)key))
        {
            Money money = (Money)(g_hash_table_lookup(_maxSpent, (char*)key));
            updateMoney(money, spent);
        }
        else if(spent != 0)
        {
            Money money = (Money)initMoney((char*)key, spent);
            g_hash_table_insert(_maxSpent, strdup((char*)key), (gpointer)money);
        }
    }
}
